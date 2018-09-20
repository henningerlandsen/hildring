#pragma once

#include "ecs/Systems.h"

namespace ecs {
template <typename Component>
class Components {
public:
    template <typename System>
    static bool link()
    {
        if (!exists) {
            exists = ecs::Systems::with<System>([](System&) {});
            return exists;
        }
        return false;
    }

private:
    static bool exists;
};

template <class Component>
bool Components<Component>::exists = false;
}
