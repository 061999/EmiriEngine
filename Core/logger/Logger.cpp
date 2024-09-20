#include "Logger.h"
#include <cstdarg>
#include <mutex>

namespace utl {

	static struct
	{
		std::array<LogBase*, 0xFF> logs;
		size_t logs_count;

		LogBuffer m_LogBuf;
		std::mutex log_lock;
	}global{};

	void dispatch_log(LOG_TYPE type, const char* file, int line, const char* format_msg)
	{
		LogMessage *msg_item{};
		if (format_msg != nullptr)
		{
			std::lock_guard<std::mutex> lg{ global.log_lock };
			global.m_LogBuf.push_log(type, utl::string{ format_msg }, file, line);
			msg_item = &(global.m_LogBuf.m_LinearBuf.back());
		}
		else
		{
			std::lock_guard<std::mutex> lg{ global.log_lock };
			global.m_LogBuf.push_log(type, "Log Stack Overflow", file, line);
			msg_item = &(global.m_LogBuf.m_LinearBuf.back());
		}

		for (size_t i = 0; (i < global.logs_count) && (nullptr != msg_item); i++)
		{
			global.logs[i]->recv_log(msg_item);
		}
	}

	void dispatch_log_v(LOG_TYPE type, const char* file, int line, const char* format_msg, ...)
	{
		std::array<char, 0x1FF> buf{};

		va_list args;
		va_start(args, format_msg);
		auto str_size = vsprintf(buf.data(), format_msg, args);
		va_end(args);

		LogMessage *msg_item{};
		if (str_size > 0)
		{
			std::lock_guard<std::mutex> lg{ global.log_lock };
			global.m_LogBuf.push_log(type, utl::string{ buf.data(),static_cast<size_t>(str_size) }, file, line);
			msg_item = &(global.m_LogBuf.m_LinearBuf.back());
		}
		else
		{
			std::lock_guard<std::mutex> lg{ global.log_lock };
			global.m_LogBuf.push_log(type, "Log Stack Overflow", file, line);
			msg_item = &(global.m_LogBuf.m_LinearBuf.back());
		}

		for (size_t i = 0; (i < global.logs_count) && (nullptr != msg_item); i++)
		{
			global.logs[i]->recv_log(msg_item);
		}
	}

	LogBase::LogBase()
	{
		global.logs[global.logs_count++] = this;
	}
}