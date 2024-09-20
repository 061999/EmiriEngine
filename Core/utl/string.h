#pragma once
//#include <eastl/string.h>
//#include "allocator.h"
//#include <EASTL/string_view.h>
#include <string>
#include "allocator.h"

namespace utl
{
	//using string = eastl::basic_string<char, allocator>;
	//using wstring = eastl::basic_string<wchar_t, allocator>;
	//using string8 = eastl::basic_string<char, allocator>;
	//using string16 = eastl::basic_string<char16_t, allocator>;
	//using string32 = eastl::basic_string<char32_t, allocator>;
	////using u8string = eastl::basic_string<char8_t, allocator>;
	//using u16string = eastl::basic_string<char16_t, allocator>;
	//using u32string = eastl::basic_string<char32_t, allocator>;

	//using string_view = eastl::basic_string_view<char>;
	//using wstring_view = eastl::basic_string_view<wchar_t>;

	//using string_view_list = eastl::basic_string_view<string_view>;

	using string = std::basic_string<char, std::char_traits<char>, allocator<char>>;
	using wstring = std::basic_string<wchar_t, std::char_traits<wchar_t>, allocator<wchar_t>>;

	template<typename T>
	struct basic_view
	{
		const T* data;
		size_t size;
		basic_view(const T* data, size_t size) : data(data), size(size) {}

		template<size_t N>
		constexpr basic_view(const char(&arr)[N]) : data(arr), size(N - 1) {}

		constexpr basic_view() : data(nullptr), size(0) {}
	};

	using string_view = basic_view<char>;
	using wstring_view = basic_view<wchar_t>;
	using string_view_list = basic_view<string_view>;
}