#include <array>
#include "resource.h"
#include "hash_map.h"
#include "vector.h"

namespace res
{
#pragma pack(1)
	struct TreeItem
	{
		u32 name_offset;
		u16 type;
		u32 resource_count;
		u32 unknow[3];
	};

	struct DChar
	{
		constexpr DChar(u8 _a, u8 _b) :
			a{ _a },
			b{ _b }
		{}

		u8 a;
		u8 b;
	};

	struct ResourceName
	{
		u16 name_length;
		u32 hash_code;
		DChar name[0x10000];
	};

	static utl::hash_map<utl::string, ResourceView> global_resource{};

	ResourceView GetResource(const char* name)
	{
		utl::string key{ name };
		auto iter = global_resource.find(key);
		if (iter == global_resource.end())
		{
			return ResourceView{};
		}
		return iter->second;
	}

#pragma pack()
}

template <typename T>
inline T EndianData(T val)
{
	return {};
}

template <>
inline u16 EndianData(u16 val)
{
	return ((val & 0xFF00) >> 8) | ((val & 0x00FF) << 8);
}

template <>
inline u32 EndianData(u32 val)
{
	return ((val & 0x000000FF) << 24) | ((val & 0x00FF0000) >> 8) | ((val & 0x0000FF00) << 8) | ((val & 0xFF000000) >> 24);
}

bool qRegisterResourceData(int, const unsigned char* tree, const unsigned char* names, const unsigned char* datas)
{
	res::TreeItem* header = (res::TreeItem*)tree;
	u32 resource_count = EndianData(header->resource_count);

	size_t name_offset{};
	size_t data_offset{};

	for (u32 i = 0; i < resource_count; i++)
	{
		res::ResourceName* name = (res::ResourceName*)&names[name_offset];
		u16 name_length = EndianData(name->name_length);
		name_offset += (sizeof(res::ResourceName::name_length) + sizeof(res::ResourceName::hash_code) + (name_length * 2));

		res::ResourceView rv{};
		rv.size = EndianData(*((u32*)&datas[data_offset]));
		rv.data = (&datas[data_offset + sizeof(res::ResourceView::size)]);
		data_offset += (sizeof(res::ResourceView::size) + rv.size);

		utl::string key{};
		key.resize(name_length);

		for (u16 i = 0; i < name_length; i++)
		{
			key[i] = (static_cast<char>(name->name[i].b));
		}

		res::global_resource[key] = rv;
	}

	return true;
}

bool qUnregisterResourceData(int, const unsigned char*, const unsigned char*, const unsigned char*)
{
	return true;
}