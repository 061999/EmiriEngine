//
// Created by primal on 24-9-20.
//
#pragma once

#ifndef VKRENDERCONTEXT_H
#define VKRENDERCONTEXT_H

#include "vk_common.h"

struct GLFWwindow;

namespace Emiri
{
    struct VkSwapChain;

    struct VkRenderContext : VkObject
    {
        VkRenderContext();
        ~VkRenderContext();
        VkSwapChain* CreateSwapchain(GLFWwindow* display);
        bool is_init;
    };

    VkRenderContext& GetRC();
}
#endif //VKRENDERCONTEXT_H
