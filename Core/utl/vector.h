#pragma once

#include <vector>
#include "allocator.h"

namespace utl
{
	template <typename T>
	using vector = std::vector<T, allocator<T>>;

	template <typename T>
	void vector_delete(vector<T> &vec, typename vector<T>::iterator iter)
	{
		if (vec.size() > 1)
		{
			(*iter) = vec.back();
			vec.pop_back();
		}
		else
		{
			vec.clear();
		}
	}

	template <typename T>
	void vector_delete_element(vector<T> &vec,T element)
	{
		for (auto itor = vec.begin(); itor != vec.end(); itor++)
		{
			if (*itor == element)
			{
				vector_delete(vec, itor);
				break;
			}
		}
	}
}