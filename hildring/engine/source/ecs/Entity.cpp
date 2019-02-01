#include "ecs/Entity.h"
#include "events/Events.h"

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
    : id_(getNextId())
{
}

Entity::~Entity()
{
    events::dispatch(OnDestroy{ id_ });
}

Entity::Entity(Entity&& other)
    : id_(other.id_)
{
    other.id_.invalidate();
}

Entity&
Entity::operator=(Entity&& other)
{
    if (this != &other) {
        id_ = other.id_;
        other.id_.invalidate();
    }
    return *this;
}

}
