#pragma once
#include <array>
#include <Core/utl/common.h>

#define WINDOWS_SURFACE "VK_KHR_win32_surface"

#define LINUX_SURFACE "VK_KHR_xcb_surface"

namespace Emiri
{
    namespace vkx
    {
        constexpr u32 vkx_version{VK_MAKE_VERSION(0, 0, 1)};
        constexpr auto vkx_name{"vkx"};
#ifdef NDEBUG
        constexpr std::array<const char *, 2> vkx_extensions{};
        constexpr std::array<const char *, 2> vkx_layers{};
#else
        constexpr std::array<const char *, 4> vkx_extensions{
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
            VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
            VK_KHR_SURFACE_EXTENSION_NAME,
#ifdef WIN32
            WINDOWS_SURFACE,
#else
            LINUX_SURFACE,
#endif
        };
        constexpr std::array<const char *, 1> vkx_layers{
            "VK_LAYER_KHRONOS_validation"
        };

#endif
        constexpr std::array<const char *, 1> vkx_device_extensions{
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        constexpr std::array<const char *, 0> vkx_device_layers{};

        struct instance_create_info : VkInstanceCreateInfo
        {
            VkInstanceCreateInfo *init()
            {
                this->_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
                this->_app_info.apiVersion = VK_API_VERSION_1_3;
                this->_app_info.applicationVersion = vkx_version;
                this->_app_info.engineVersion = vkx_version;
                this->_app_info.pEngineName = vkx_name;
                this->_app_info.pApplicationName = vkx_name;
                this->_app_info.pNext = nullptr;

                sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                pNext = nullptr;
                flags = 0;
                pApplicationInfo = &_app_info;
                enabledLayerCount = static_cast<uint32_t>(vkx_layers.size());
                ppEnabledLayerNames = vkx_layers.data();
                enabledExtensionCount = static_cast<uint32_t>(vkx_extensions.size());
                ppEnabledExtensionNames = vkx_extensions.data();

                return this;
            }

        private:
            VkApplicationInfo _app_info;
        };

        template<u32 family_count>
        struct device_create_info : VkDeviceCreateInfo
        {
            void init_queue(u32 fam_index, u32 fam_id, float *priorites, u32 count)
            {
                VkDeviceQueueCreateInfo &info{queue_create_infos[fam_index]};
                info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                info.pNext = nullptr;
                info.flags = 0;
                info.queueFamilyIndex = fam_id;
                info.queueCount = count;
                info.pQueuePriorities = priorites;
            }

            VkDeviceCreateInfo *init()
            {
                features = {};
                sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                pNext = nullptr;
                flags = 0;
                queueCreateInfoCount = family_count;
                pQueueCreateInfos = queue_create_infos;
                enabledLayerCount = static_cast<u32>(vkx_device_layers.size());
                ppEnabledLayerNames = vkx_device_layers.data();
                enabledExtensionCount = static_cast<u32>(vkx_device_extensions.size());
                ppEnabledExtensionNames = vkx_device_extensions.data();
                pEnabledFeatures = &features;
                return this;
            }

        private:
            VkDeviceQueueCreateInfo queue_create_infos[family_count];
            VkPhysicalDeviceFeatures features;
        };

        struct debug_create_info
        {
            VkDebugReportCallbackCreateInfoEXT *as_report(PFN_vkDebugReportCallbackEXT callback)
            {
                report_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
                report_info.pNext = nullptr;
                report_info.flags = 0;
                report_info.pfnCallback = callback;
                report_info.pUserData = nullptr;
                return &report_info;
            }

            VkDebugUtilsMessengerCreateInfoEXT *as_utils(PFN_vkDebugUtilsMessengerCallbackEXT callback)
            {
                utils_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
                utils_info.pNext = nullptr;
                utils_info.flags = 0;
                utils_info.messageSeverity = 0b1111;
                utils_info.messageType = 0b1111;
                utils_info.pfnUserCallback = callback;
                utils_info.pUserData = nullptr;
                return &utils_info;
            }

        private:
            union
            {
                VkDebugReportCallbackCreateInfoEXT report_info;
                VkDebugUtilsMessengerCreateInfoEXT utils_info;
            };
        };

        struct SwapchainCreateInfo : VkSwapchainCreateInfoKHR
        {
            VkSwapchainCreateInfoKHR* init()
            {
                this->sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
                this->pNext = nullptr;
                this->flags = 0;
                //VkSurfaceKHR                     surface;
                //uint32_t                         minImageCount;
                //VkFormat                         imageFormat;
                //VkColorSpaceKHR                  imageColorSpace;
                //VkExtent2D                       imageExtent;
                //uint32_t                         imageArrayLayers;
                //VkImageUsageFlags                imageUsage;
                //VkSharingMode                    imageSharingMode;
                //uint32_t                         queueFamilyIndexCount;
                //const uint32_t*                  pQueueFamilyIndices;
                //VkSurfaceTransformFlagBitsKHR    preTransform;
                //VkCompositeAlphaFlagBitsKHR      compositeAlpha;
                //VkPresentModeKHR                 presentMode;
                //VkBool32                         clipped;
                //VkSwapchainKHR                   oldSwapchain;
                return this;
            }
        };
    } // namespace vkx
} // namespace Emiri