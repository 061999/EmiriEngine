#pragma once

#ifndef UTL_ALLOCATOR_H
#define UTL_ALLOCATOR_H

#ifdef USE_MI_ALLOCATOR
#include <mimalloc.h>
#else
#include <vector>
#endif

namespace utl
{
#ifdef USE_MI_ALLOCATOR
    template<typename T>
    using allocator = mi_stl_allocator<T>;
#else
    template<typename T>
    using allocator = std::allocator<T>;
#endif
}

#endif