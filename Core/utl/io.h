#pragma once
#include <utl/vector.h>
#include <common_header.h>

namespace utl
{
    using filebytes = utl::vector<u8>;
    bool read_file(const char* path, filebytes& storage);
    //bool read_file_w(const wchar_t* path, utl::vector<u8>& storage);
}