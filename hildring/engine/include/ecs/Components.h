#pragma once

namespace ecs {
class Components {

    template <class Component>
    class ComponentProxy {
    public:
        static bool exists;
    };

public:
    template <typename System, typename Component>
    static bool add()
    {
        if (!ComponentProxy<Component>::exists) {
            ComponentProxy<Component>::exists = true;
            return true;
        }
        return false;
    }
};

template <class Component>
bool Components::ComponentProxy<Component>::exists = false;
}
