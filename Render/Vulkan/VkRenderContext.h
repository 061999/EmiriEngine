//
// Created by primal on 24-9-20.
//
#pragma once

#ifndef VKRENDERCONTEXT_H
#define VKRENDERCONTEXT_H

#include "vk_common.h"

namespace Emiri
{
    struct VkRenderContext : VkObject
    {
        VkRenderContext();
        ~VkRenderContext();
        bool is_init;
    };

    VkRenderContext& GetRC();
}
#endif //VKRENDERCONTEXT_H
