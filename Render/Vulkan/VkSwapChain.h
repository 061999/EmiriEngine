//
// Created by primal on 24-9-21.
//

#pragma once

#ifndef VKSWAPCHAIN_H
#define VKSWAPCHAIN_H

#include "vk_common.h"

namespace Emiri
{
    struct VkSwapChain : VkObject
    {
        VkSurfaceKHR vk_surface_khr;
        VkSwapchainKHR vk_swap_chain_khr;
    };
}
#endif //VKSWAPCHAIN_H