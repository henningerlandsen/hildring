#pragma once

#include "ecs/EntityId.h"

namespace ecs {
class Entity {
public:
    Entity();
    ~Entity();

    EntityId getId() const { return id; }

private:
    const EntityId id;
};
}
