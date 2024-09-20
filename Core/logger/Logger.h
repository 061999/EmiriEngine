#pragma once

#include <Core/utl/deque.h>
#include <Core/utl/string.h>
#include <array>

namespace utl
{
    enum LOG_TYPE : int
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        TERROR,
        CRITICAL,
        LOG_TYPE_NUM,
        LOG_TYPE_NONE = 0x0000,
        TRACE_BIT = 0x0001,
        DEBUG_BIT = 0x0002,
        INFO_BIT = 0x0004,
        WARN_BIT = 0x0008,
        ERROR_BIT = 0x0010,
        CRITICAL_BIT = 0x0020,
        LOG_TYPE_MASK_BIT = TRACE_BIT | DEBUG_BIT | INFO_BIT | WARN_BIT | ERROR_BIT | CRITICAL_BIT,
    };

    struct LogMessage
    {
        inline LogMessage() :
            m_Type{ LOG_TYPE_NUM },

            m_Localtion{ "Error Localtion" },
            m_Message{ "Error Message" }
        {}

        inline LogMessage(LOG_TYPE type, utl::string msg, const char* file, int line) :
            m_Type{ type },
            m_Localtion{ file },
            m_Message{std::move( msg )}
        {}

        LOG_TYPE m_Type;

        utl::string m_Localtion;
        utl::string m_Message;
    };

    struct LogBuffer
    {
        inline LogBuffer() :
            m_LinearBuf{},
            m_SortBuf{},
            m_MaxLength{ 0xFFFF }
        {}
        utl::deque<LogMessage> m_LinearBuf;
        std::array<utl::deque<LogMessage>, LOG_TYPE_NUM> m_SortBuf;
        size_t m_MaxLength;

        inline void trim_buffer(utl::deque<LogMessage>& buf) const
        {
            while (buf.size() > m_MaxLength)
            {
                buf.pop_front();
            }
        }

        inline void push_log(LOG_TYPE type, const utl::string& msg, const char* file, int line)
        {
            trim_buffer(m_LinearBuf);
            m_LinearBuf.emplace_back(type, msg, file, line);
            trim_buffer(m_SortBuf[type]);
            m_SortBuf[type].emplace_back(type, msg, file, line);
        }
    };

    ///使用静态注册，不需要析构函数
    class LogBase
    {
    public:
        LogBase();
        virtual ~LogBase() = default;

        virtual void recv_log(LogMessage* msg) = 0;
    };

    void dispatch_log_v(LOG_TYPE type, const char* file, int line, const char* format_msg, ...);
    void dispatch_log(LOG_TYPE type, const char* file, int line, const char* format_msg);
}

#ifndef NDEBUG
#define LOG_TRACE_V(msg,...) utl::dispatch_log_v(utl::TRACE,__FILE__,__LINE__,msg,__VA_ARGS__)
#define LOG_TRACE(msg) utl::dispatch_log(utl::TRACE,__FILE__,__LINE__,msg)

#define LOG_DEBUG_V(msg,...) utl::dispatch_log_v(utl::DEBUG,__FILE__,__LINE__,msg,__VA_ARGS__)
#define LOG_DEBUG(msg) utl::dispatch_log(utl::DEBUG,__FILE__,__LINE__,msg)

#define LOG_INFO_V(msg,...) utl::dispatch_log_v(utl::INFO,__FILE__,__LINE__,msg,__VA_ARGS__)
#define LOG_INFO(msg) utl::dispatch_log(utl::INFO,__FILE__,__LINE__,msg)

#define LOG_WARN_V(msg,...) utl::dispatch_log_v(utl::WARN,__FILE__,__LINE__,msg,__VA_ARGS__)
#define LOG_WARN(msg) utl::dispatch_log(utl::WARN,__FILE__,__LINE__,msg)

#define LOG_ERROR_V(msg,...) utl::dispatch_log_v(utl::TERROR,__FILE__,__LINE__,msg,__VA_ARGS__)
#define LOG_ERROR(msg) utl::dispatch_log(utl::TERROR,__FILE__,__LINE__,msg)

#define LOG_CRITICAL_V(msg,...) utl::dispatch_log_v(utl::CRITICAL,__FILE__,__LINE__,msg,__VA_ARGS__)
#define LOG_CRITICAL(msg) utl::dispatch_log(utl::CRITICAL,__FILE__,__LINE__,msg)

#else
#define LOG_TRACE_V(msg,...) void(0)
#define LOG_TRACE(msg) void(0)

#define LOG_DEBUG_V(msg,...) void(0)
#define LOG_DEBUG(msg) void(0)

#define LOG_INFO_V(msg,...) utl::dispatch_log_v(utl::INFO,__FILE__,__LINE__,msg,__VA_ARGS__)
#define LOG_INFO(msg) utl::dispatch_log(utl::INFO,__FILE__,__LINE__,msg)

#define LOG_WARN_V(msg,...) utl::dispatch_log_v(utl::WARN,__FILE__,__LINE__,msg,__VA_ARGS__)
#define LOG_WARN(msg) utl::dispatch_log(utl::WARN,__FILE__,__LINE__,msg)

#define LOG_ERROR_V(msg,...) utl::dispatch_log_v(utl::TERROR,__FILE__,__LINE__,msg,__VA_ARGS__)
#define LOG_ERROR(msg) utl::dispatch_log(utl::TERROR,__FILE__,__LINE__,msg)

#define LOG_CRITICAL_V(msg,...) utl::dispatch_log_v(utl::CRITICAL,__FILE__,__LINE__,msg,__VA_ARGS__)
#define LOG_CRITICAL(msg) utl::dispatch_log(utl::CRITICAL,__FILE__,__LINE__,msg)
#endif // NDEBUG
