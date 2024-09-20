#include <cstdio>
#include <unistd.h>
#include <Core/utl/async.h>

#include "Core/utl/memory.h"
#include <Core/logger/Logger.h>

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
    utl::task_pool::serverInstance().start(utl::make_pointer<my_class>());
    sleep(4);
    return 0;
}