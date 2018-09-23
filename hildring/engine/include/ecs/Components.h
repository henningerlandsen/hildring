#pragma once

#include "ecs/EntityId.h"
#include "ecs/Systems.h"

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
            createFn = [](const ecs::EntityId id, Component*& component) {
                bool created = false;
                ecs::Systems::with<System>([&created, id, &component](System& system) {
                    created = system.create(id, component);
                });
                return created;
            };
            return LinkLifetime(true);
        }
        return LinkLifetime(false);
    }

    template <typename Callable>
    static bool create(const ecs::EntityId id, Callable&& callback)
    {
        if (linked()) {
            Component* component = nullptr;
            createFn(id, component);
            if (component) {
                callback(*component);
                return true;
            }
        }
        return false;
    }

    static bool create(const ecs::EntityId id)
    {
        return create(id, [](Component&) {});
    }

    template <typename Callable>
    static bool with(const ecs::EntityId, Callable&&)
    {
        return false;
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

    static bool (*createFn)(const ecs::EntityId, Component*&);
};

template <class Component>
bool (*Components<Component>::createFn)(const ecs::EntityId, Component*&) = nullptr;
}
