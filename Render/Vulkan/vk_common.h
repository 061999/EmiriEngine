//
// Created by primal on 24-9-20.
//
#pragma once

#ifndef VK_COMMON_H
#define VK_COMMON_H

#include <Core/volk/volk.h>

namespace Emiri
{
    struct VkObject
    {
        static VkInstance vk_instance;
        static VkDevice vk_device;
        static VolkDeviceTable dev;
    };

    const VkAllocationCallbacks* GetVkAlloc();
}
#endif //VK_COMMON_H
