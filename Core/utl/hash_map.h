#pragma once
#include "allocator.h"
#include <unordered_map>
#include "./string.h"

//namespace eastl
//{
//	template <typename T> struct hash<utl::string> // Note that we use the pointer as-is and don't divide by sizeof(T*). This is because the table is of a prime size and this division doesn't benefit distribution.
//	{
//		size_t operator()(T* p) const { return 1; }
//	};
// 
// template <typename T = void>
//struct equal_to : public binary_function<T, T, bool>
//{
//	EA_CPP14_CONSTEXPR bool operator()(const T& a, const T& b) const
//	{
//		return a == b;
//	}
//};

//}
namespace utl
{
	
	template<typename TK,typename TV>
	using hash_map = std::unordered_map<TK, TV, std::hash<TK>, std::equal_to<TK>, allocator<std::pair<const TK, TV>>>;

	template<typename TK, typename TV, typename TH, typename TE = std::equal_to<TK>>
	using unordered_map = std::unordered_map<TK, TV, TH, TE, allocator<std::pair<TK, TV>>>;
	//template<typename TK,typename TV>
	//using hash_map = std::unordered_map<TK, TV,std::hash<TK>,std::equal_to<TK>, mi_stl_allocator<std::pair<const TK, TV>>>;

	struct hash_string
	{
		inline size_t operator()(const string& x) const
		{
			const unsigned char* p = (const unsigned char*)x.c_str(); // To consider: limit p to at most 256 chars.
			unsigned int c, result = 2166136261U; // We implement an FNV-like string hash.
			while ((c = *p++) != 0) // Using '!=' disables compiler warnings.
				result = (result * 16777619) ^ c;
			return (size_t)result;
		}
	};

	template<typename T>
	using string_map = unordered_map<string, T, hash_string>;
}