#pragma once
#include <common_header.h>
#include <string>

namespace utl
{
	struct image
	{
		u8* data;
		s32 width;
		s32 height;
		s32 channel;

		image(const char*);
		//image(const std::string&);
		image(u8* data, u32 size);
		template<typename T>
		image(T& container) :image{(u8*)container.data(),(u32)container.size()}
		{}
		~image();
	};
}