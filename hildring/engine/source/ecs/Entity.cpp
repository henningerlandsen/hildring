#include "ecs/Entity.h"

namespace ecs {
namespace {
    EntityId topId = 0;
    EntityId generateId()
    {
        topId = topId + 1;
        return topId;
    }
}
Entity::Entity()
    : id(generateId())
{
}

Entity::~Entity() {}
}
