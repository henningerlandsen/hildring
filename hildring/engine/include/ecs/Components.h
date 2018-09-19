#pragma once

namespace ecs {
template <typename Component>
class Components {
public:
    template <typename System>
    static bool link()
    {
        if (!exists) {
            exists = true;
            return true;
        }
        return false;
    }

private:
    static bool exists;
};

template <class Component>
bool Components<Component>::exists = false;
}
