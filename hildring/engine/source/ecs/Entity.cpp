#include "ecs/Entity.h"

namespace ecs {
namespace {
    EntityId topId = 0;
    EntityId getNextId()
    {
        topId = topId + 1;
        return topId;
    }
}
Entity::Entity()
    : _id(getNextId())
{
}

Entity::~Entity() {}
}
