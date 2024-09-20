#pragma once

#include <chrono>

namespace utl
{
	using time = std::chrono::system_clock;
	using time_point = time::time_point;
	using duration = std::chrono::duration<float>;
	using duration_d = std::chrono::duration<double>;
}