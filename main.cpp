#include <cstdio>
#include <unistd.h>
#include <Core/utl/async.h>

#include "Core/utl/memory.h"
#include <Core/logger/Logger.h>
#include <Render/Vulkan/VkRenderContext.h>

class my_class : public utl::task_base
{
public:
    my_class() { this->auto_free = true; }
    void action(const bool& par_life) override
    {
        while (par_life)
        {
            LOG_INFO("asdf");
        }
    }
};

int main()
{
    auto isinit = Emiri::GetRC().is_init;
    return 0;
}