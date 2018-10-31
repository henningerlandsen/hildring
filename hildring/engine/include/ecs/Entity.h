#pragma once

#include "ecs/Components.h"
#include "ecs/EntityId.h"
#include "util/LifetimeToken.h"

#include <vector>

namespace ecs {
class Entity {
public:
    Entity();
    ~Entity();

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    Entity(Entity&& other);
    Entity& operator=(Entity&& other);

    EntityId id() const { return id_; }

    template <typename Component, typename Callable>
    bool add(Callable&& callback);

    template <typename Component, typename Callable>
    bool with(Callable&& callback);

    template <typename Component>
    bool destroy();

private:
    EntityId id_;
    std::vector<util::LifetimeToken> tokens_;
};

template <typename Component, typename Callable>
bool Entity::add(Callable&& callback)
{
    if (Components<Component>::create(id_, callback)) {
        EntityId id = id_;
        tokens_.emplace_back([id]() {
            Components<Component>::destroy(id);
        });
        return true;
    }
    return false;
}

template <typename Component, typename Callable>
bool Entity::with(Callable&& callback)
{
    return Components<Component>::with(id_, callback);
}

template <typename Component>
bool Entity::destroy()
{
    return Components<Component>::destroy(id_);
}
}
