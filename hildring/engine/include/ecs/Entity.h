#pragma once

#include "ecs/Components.h"
#include "ecs/EntityId.h"

namespace ecs {
class Entity {
public:
    Entity();
    ~Entity();

    EntityId id() const { return _id; }

    template <typename Component, typename Callable>
    bool add(Callable&& callback);

private:
    const EntityId _id;
};

template <typename Component, typename Callable>
bool Entity::add(Callable&& callback)
{
    return Components<Component>::create(_id, callback);
}
}
