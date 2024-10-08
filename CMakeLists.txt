cmake_minimum_required(VERSION 3.5)

project(EmiriEngine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("3rd/glfw")
add_subdirectory("3rd/spdlog")
add_subdirectory("3rd/mimalloc")
add_subdirectory("3rd/entt")
add_subdirectory("3rd/VulkanHeaders")
add_subdirectory("3rd/json")
add_subdirectory("3rd/freetype")
add_subdirectory("3rd/glm")
add_subdirectory("3rd/DirectXHeaders")

option(USE_MIMALLOC "是否使用mimalloc管理内存" ON)

set(Emiri_Header
        #Core_utl
        "Core/utl/common.h"
        "Core/utl/async.h"
        "Core/utl/allocator.h"
        "Core/utl/vector.h"
        "Core/utl/deque.h"
        "Core/utl/string.h"
        "Core/utl/memory.h"
        "Core/utl/hash_map.h"
        "Core/utl/resource.h"
        "Core/utl/time.h"
        #Volk
        "Core/volk/volk.h"
        #Core_logger
        "Core/logger/Logger.h"
        #Core_config
        "Core/config/Config.h"

        "Server/ServerBase.h"

        #Render
        "Render/RenderContext.h"

        "Render/Vulkan/vk_common.h"
        "Render/Vulkan/helper.h"
        "Render/Vulkan/VkRenderContext.h"
        "Render/Vulkan/VkSwapChain.h"
)

if (WIN32)
    set(Emiri_Plat_Source
            "Core/utl/async_windows.cpp"
            "Render/DirectX/dx_common.h"
            "Render/DirectX/DxRenderContext.h"
            "Render/DirectX/DxRenderContext.cpp"
            "Server/ServerBaseWindows.cpp"
    )
else ()
    set(Emiri_Plat_Source
            "Core/utl/async_linux.cpp"
            "Server/ServerBaseLinux.cpp"
    )
endif ()

set(py_third_party_path "${CMAKE_CURRENT_LIST_DIR}/3rd")

set(Emiri_Source
        "main.cpp"
        "${Emiri_Header}"
        "${Emiri_Plat_Source}"
        #Core_utl
        "Core/utl/rcc_resource.cpp"
        #Volk
        "Core/volk/volk.c"
        #Core_logger
        "Core/logger/Logger.cpp"
        "Core/logger/ConsoleLog.cpp"
        #Core_config
        "Core/config/ConfigImplJson.cpp"
        #Render
        "Render/RenderContext.cpp"

        "Render/Vulkan/VkRenderContext.cpp"
        "Render/Vulkan/VkSwapChain.cpp"

        "Server/ServerBase.cpp"
)

#创建Emiri程序
add_executable(${CMAKE_PROJECT_NAME} ${Emiri_Source})

#链接第三方库
target_link_libraries(${CMAKE_PROJECT_NAME}
        "spdlog"
        "Vulkan::Headers"
        "nlohmann_json"
        "freetype"
        "glfw"
        "Microsoft::DirectX-Headers"
)

if(WIN32)
    target_link_libraries(${CMAKE_PROJECT_NAME} "d3d12" "dxgi")
endif()

if (${USE_MIMALLOC})
    message("使用了mimalloc管理内存")
    target_link_libraries(${CMAKE_PROJECT_NAME} "mimalloc-static")
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE "USE_MI_ALLOCATOR")
else ()
    message("没有使用mimalloc管理内存")
endif ()

#设置包含路径
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}"
)