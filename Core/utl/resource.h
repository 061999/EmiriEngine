#pragma once

#include "common.h"

namespace res
{
	struct ResourceView
	{
		u32 size;
		const u8* data;
	};

	ResourceView GetResource(const char*);
}