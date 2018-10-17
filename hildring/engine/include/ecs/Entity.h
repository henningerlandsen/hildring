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

    EntityId id() const { return _id; }

    template <typename Component, typename Callable>
    bool add(Callable&& callback);

    template <typename Component, typename Callable>
    bool with(Callable&& callback);

    template <typename Component>
    bool destroy();

private:
    EntityId _id;
    //    std::vector<util::LifetimeToken> tokens;
};

template <typename Component, typename Callable>
bool Entity::add(Callable&& callback)
{
    return Components<Component>::create(_id, callback);
}

template <typename Component, typename Callable>
bool Entity::with(Callable&& callback)
{
    return Components<Component>::with(_id, callback);
}

template <typename Component>
bool Entity::destroy()
{
    return Components<Component>::destroy(_id);
}
}
