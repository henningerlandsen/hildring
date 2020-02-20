#pragma once

#include "ecs/EntityId.h"
#include "ecs/Systems.h"
#include "util/LifetimeToken.h"

namespace ecs {
template <typename Component>
class Components {
    using MutatingFn = bool (*)(const ecs::EntityId, Component*&);
    using DestroyFn = bool (*)(const ecs::EntityId);

public:
    template <typename System>
    static util::LifetimeToken link()
    {
        if (!linked()) {
            createFn = [](const ecs::EntityId id, Component*& component) {
                bool created = false;
                ecs::Systems<System>::with([&created, id, &component](System& system) {
                    created = system.create(id, component);
                });
                return created;
            };
            getFn = [](const ecs::EntityId id, Component*& component) {
                bool found = false;
                ecs::Systems<System>::with([&found, id, &component](System& system) {
                    found = system.get(id, component);
                });
                return found;
            };
            destroyFn = [](const ecs::EntityId id) {
                bool destroyed = false;
                ecs::Systems<System>::with([&destroyed, id](System& system) {
                    destroyed = system.destroy(id);
                });
                return destroyed;
            };
            return util::LifetimeToken([]() {
                Components<Component>::unlink();
            });
        }
        return util::LifetimeToken();
    }

    template <typename Callable>
    static bool create(const ecs::EntityId id, Callable&& callback)
    {
        return call(createFn, id, callback);
    }

    static bool create(const ecs::EntityId id)
    {
        return create(id, [](Component&) {});
    }

    template <typename Callable>
    static bool with(const ecs::EntityId id, Callable&& callback)
    {
        return call(getFn, id, callback);
    }

    static bool destroy(const ecs::EntityId id)
    {
        return linked() ? destroyFn(id) : false;
    }

private:
    static void unlink()
    {
        createFn = nullptr;
        getFn = nullptr;
        destroyFn = nullptr;
    }

    static bool linked()
    {
        return createFn != nullptr && getFn != nullptr && destroyFn != nullptr;
    }

    template <typename Callable>
    static bool call(MutatingFn method, const ecs::EntityId id, Callable&& callback)
    {
        if (linked()) {
            Component* component = nullptr;
            method(id, component);
            if (component) {
                callback(*component);
                return true;
            }
        }
        return false;
    }

    static MutatingFn createFn;
    static MutatingFn getFn;
    static DestroyFn destroyFn;
};

template <class Component>
typename Components<Component>::MutatingFn Components<Component>::createFn = nullptr;

template <class Component>
typename Components<Component>::MutatingFn Components<Component>::getFn = nullptr;

template <class Component>
typename Components<Component>::DestroyFn Components<Component>::destroyFn = nullptr;
}
