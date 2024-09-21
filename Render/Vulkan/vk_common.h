//
// Created by primal on 24-9-20.
//
#pragma once

#ifndef VK_COMMON_H
#define VK_COMMON_H

#include <Core/volk/volk.h>
#include <Core/utl/common.h>

namespace Emiri
{
    static constexpr u32 FRAME_BUFFER_COUNT{4u};

    struct VkObject
    {
        static VkInstance vk_instance;
        static VkDevice vk_device;
        static VkQueue vk_direct_queue;
        static VkQueue vk_copy_queue;
    };

    const VkAllocationCallbacks *GetVkAlloc();
}
#endif //VK_COMMON_H