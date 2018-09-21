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
            auto& createFn2 = createFn;
            exists = ecs::Systems::with<System>([&createFn2](System& system) {
                createFn2 = [&system](Component*& component) {
                    return system.create(component);
                };
            });
            return exists;
        }
        return false;
    }

    template <typename Callable>
    static bool create(Callable&& callback)
    {
        Component* component = nullptr;
        createFn(component);
        if (component) {
            callback(*component);
            return true;
        }
        return false;
    }

private:
    static bool exists;
    static std::function<bool(Component*&)> createFn;
};

template <class Component>
bool Components<Component>::exists = false;

template <class Component>
std::function<bool(Component*&)> Components<Component>::createFn;
}
