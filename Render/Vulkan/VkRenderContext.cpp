//
// Created by primal on 24-9-20.
//

#include "VkRenderContext.h"
#include "helper.h"
#include <Core/logger/Logger.h>

#include "Core/utl/vector.h"

VkInstance Emiri::VkObject::vk_instance{};
VkDevice Emiri::VkObject::vk_device;

const VkAllocationCallbacks *Emiri::GetVkAlloc()
{
    return nullptr;
}

Emiri::VkRenderContext::VkRenderContext(): is_init{false}
{
    if (VK_SUCCESS != volkInitialize())
    {
        LOG_ERROR("Initialize VOLK Error");
        return;
    }

    //验证层检测
    u32 layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    utl::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount,availableLayers.data());

    u32 extCount;
    vkEnumerateInstanceExtensionProperties(&extCount,nullptr,);

    vkx::instance_create_info _ins_info{};
    if (VK_SUCCESS != vkCreateInstance(_ins_info.init(), GetVkAlloc(), &vk_instance))
    {
        LOG_ERROR("Create VKInstance Error");
        return;
    }
    volkLoadInstance(vk_instance);

    is_init = true;
}

Emiri::VkRenderContext::~VkRenderContext()
{
    vkDestroyInstance(vk_instance, GetVkAlloc());
}

Emiri::VkRenderContext &Emiri::GetRC()
{
    static VkRenderContext vkrc{};
    return vkrc;
}