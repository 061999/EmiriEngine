#pragma once

#include <memory>
#include "allocator.h"


namespace utl
{
	namespace _internal
	{
		template <typename T>
		struct default_delete
		{
			constexpr default_delete() noexcept = default;

			inline void operator()(T* p) const noexcept
			{
				allocator<T> stl_allocator;
				stl_allocator.destroy(p);
				stl_allocator.deallocate(p,1);
			}
		};
	}

	template <typename T>
	using shared_ptr = std::shared_ptr<T>;

	template <class Ty, class... Types>
	inline shared_ptr<Ty> make_shared(Types&&... Args)
	{
		allocator<Ty> stl_allocator;
		auto empty_ptr = stl_allocator.allocate(1);
		stl_allocator.construct(empty_ptr,std::forward<Types>(Args)...);
		return shared_ptr<Ty>{ empty_ptr,_internal::default_delete<Ty>{} };
	}

	template<typename T>
	using unique_ptr = std::unique_ptr<T, _internal::default_delete<T>>;

	template <typename T, typename... Args>
	inline unique_ptr<T> make_unique(Args&&... args)
	{
		allocator<T> stl_allocator;
		auto null_ptr = stl_allocator.allocate(1);
		stl_allocator.construct(null_ptr,std::forward<Args>(args)...);
		return unique_ptr<T>(null_ptr);
	}

	template <typename T, typename... Args>
	inline T* make_pointer(Args&&...args)
	{
		allocator<T> stl_allocator;
		auto null_ptr = stl_allocator.allocate(1);
		stl_allocator.construct(null_ptr,std::forward<Args>(args)...);
		return null_ptr;
	}

	template<typename T>
	inline void free_pointer(T* ptr)
	{
		allocator<T> stl_allocator;
		stl_allocator.destroy(ptr);
		stl_allocator.deallocate(ptr,1);
	}
}