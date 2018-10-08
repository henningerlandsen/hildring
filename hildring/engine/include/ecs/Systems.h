#pragma once

#include "util/Index.h"

#include <assert.h>
#include <memory>
#include <vector>

namespace ecs {
template <typename System>
class Systems {
public:
    template <typename... Args>
    static bool create(Args&&... args)
    {
        if (!valid()) {
            system = std::make_unique<System>(std::forward<Args>(args)...);
            return true;
        }
        return false;
    }

    template <typename Accessor>
    static bool with(Accessor&& accessor)
    {
        if (valid()) {
            accessor(*system);
            return true;
        }
        return false;
    }

    static void reset()
    {
        system.reset();
    }

private:
    static System* getSystem()
    {
        return system.get();
    }

    static bool valid()
    {
        return system != nullptr;
    }

    static std::unique_ptr<System> system;
};

template <typename System>
std::unique_ptr<System> Systems<System>::system;
}

