#include "Logger.h"
#include <spdlog/logger.h>
#include <spdlog/sinks/ansicolor_sink-inl.h>

namespace console_log
{
	class cl : public utl::LogBase
	{
	public:
		cl():
			log_ins{ "CL",std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>() }
		{
#ifndef NDEBUG
			log_ins.set_level(spdlog::level::trace);
#endif // NDEBUG
		}
	private:
		//LogBase
		void recv_log(utl::LogMessage* msg) override
		{
			static constexpr std::array<spdlog::level::level_enum, spdlog::level::n_levels> log_map
			{
				spdlog::level::trace,
				spdlog::level::debug ,
				spdlog::level::info ,
				spdlog::level::warn ,
				spdlog::level::err ,
				spdlog::level::critical ,
				spdlog::level::off,
			};
			log_ins.log(log_map[msg->m_Type], msg->m_Message);
		}
		spdlog::logger log_ins;
	};

	static cl register_cl{};
}
