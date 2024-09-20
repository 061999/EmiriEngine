#pragma once

#include <mimalloc.h>
#include <entt/entity/registry.hpp>

namespace utl
{
	using registry = entt::basic_registry<entt::entity, mi_stl_allocator<entt::entity>>;
}