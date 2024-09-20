#include <queue>
#include <deque>
#include "allocator.h"

namespace utl
{
	template <typename T>
	using deque = std::deque<T, allocator<T>>;
	//using deque = eastl::deque<T, allocator, (DEQUE_DEFAULT_SUBARRAY_SIZE(T) * 16)>;


	template <typename T>
	using queue = std::queue<T, deque<T>>;
	//using queue = eastl::queue<T, deque<T>>;
}