//
// Created by primal on 24-9-20.
//

#include "VkRenderContext.h"
#include "helper.h"
#include <Core/logger/Logger.h>

#include <Core/utl/vector.h>

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

#if 0
    //验证层检测
    u32 layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    utl::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());


    for (auto& item : availableLayers)
    {
        u32 ext_count;
        vkEnumerateInstanceExtensionProperties(item.layerName, &ext_count, nullptr);
        utl::vector<VkExtensionProperties> all_ext;
        all_ext.resize(ext_count);
        vkEnumerateInstanceExtensionProperties(item.layerName, &ext_count, all_ext.data());
        printf("\n");
        LOG_WARN("======Begin Layer======");

        LOG_INFO(item.layerName);
        for (auto& prop : all_ext)
        {
            LOG_DEBUG(prop.extensionName);
        }
    }
#endif // 0

    vkx::instance_create_info _ins_info{};
    if (VK_SUCCESS != vkCreateInstance(_ins_info.init(), GetVkAlloc(), &vk_instance))
    {
        LOG_ERROR("Create VKInstance Error");
        return;
    }
    volkLoadInstance(vk_instance);

    u32 _num_physical_devices{};
    vkEnumeratePhysicalDevices(vk_instance, &_num_physical_devices, nullptr);
    utl::vector<VkPhysicalDevice> _physical_devices(_num_physical_devices);
    vkEnumeratePhysicalDevices(vk_instance, &_num_physical_devices, _physical_devices.data());

    if (_physical_devices.empty())
    {
        LOG_ERROR("No Physical Device Found");
        return;
    }

    LOG_INFO("Found Physical Devices");
    for (auto phy_dev : _physical_devices)
    {
        VkPhysicalDeviceProperties phy_dev_props{};
        vkGetPhysicalDeviceProperties(phy_dev, &phy_dev_props);
        LOG_INFO(phy_dev_props.deviceName);

        u32 _num_queue_families;
        vkGetPhysicalDeviceQueueFamilyProperties(phy_dev, &_num_queue_families, nullptr);
        utl::vector<VkQueueFamilyProperties> _queue_families(_num_queue_families);
        vkGetPhysicalDeviceQueueFamilyProperties(phy_dev, &_num_queue_families, _queue_families.data());
        LOG_INFO_V("Queue Family Count: %d", _num_queue_families);
    }

    vkx::device_create_info<1> _dev_info{};
    float ppp = 1.0f;
    _dev_info.init_queue(0, 0, &ppp, 1);
    if (VK_SUCCESS != vkCreateDevice(_physical_devices[0], _dev_info.init(), GetVkAlloc(), &vk_device))
    {
        LOG_ERROR("Create VKDevice Error");
        return;
    }

    volkLoadDevice(vk_device);
    
    VkQueue que{};
    vkGetDeviceQueue(vk_device, 0, 0, &que);

    is_init = true;
}

Emiri::VkRenderContext::~VkRenderContext()
{
    //vkDestroyInstance(vk_instance, GetVkAlloc());
}

Emiri::VkRenderContext &Emiri::GetRC()
{
    static VkRenderContext vkrc{};
    return vkrc;
}