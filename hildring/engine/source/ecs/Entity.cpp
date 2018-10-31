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

Entity::Entity(Entity&& other)
    : _id(other._id)
{
    other._id.invalidate();
}

Entity&
Entity::operator=(Entity&& other)
{
    if (this != &other) {
        _id = other._id;
        other._id.invalidate();
    }
    return *this;
}

}
