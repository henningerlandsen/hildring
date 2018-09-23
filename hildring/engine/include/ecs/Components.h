#pragma once

#include "ecs/Systems.h"

#include <functional>

namespace ecs {
template <typename Component>
class Components {
public:
    class LinkLifetime {
    public:
        LinkLifetime(bool validLink)
            : valid(validLink)
        {
        }

        ~LinkLifetime()
        {
            if (valid) {
                Components<Component>::unlink();
            }
        }

        LinkLifetime(const LinkLifetime&) = delete;

        LinkLifetime(LinkLifetime&& other)
        {
            this->valid = other.valid;
            other.valid = false;
        }

        operator bool() const { return valid; }

    private:
        bool valid{ false };
    };

    template <typename System>
    static LinkLifetime link()
    {
        if (!linked()) {
            createFn = [](Component*& component) {
                bool created = false;
                ecs::Systems::with<System>([&created, &component](System& system) {
                    created = system.create(component);
                });
                return created;
            };
            return LinkLifetime(true);
        }
        return LinkLifetime(false);
    }

    template <typename Callable>
    static bool create(Callable&& callback)
    {
        if (linked()) {
            Component* component = nullptr;
            createFn(component);
            if (component) {
                callback(*component);
                return true;
            }
        }
        return false;
    }

    static bool create()
    {
        return create([](Component&) {});
    }

private:
    static void unlink()
    {
        createFn = nullptr;
    }

    static bool linked()
    {
        return createFn != nullptr;
    }

    static bool (*createFn)(Component*&);
};

template <class Component>
bool (*Components<Component>::createFn)(Component*&) = nullptr;
}
