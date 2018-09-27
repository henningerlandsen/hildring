#pragma once

#include "util/Index.h"

#include <assert.h>
#include <memory>
#include <vector>

namespace ecs {
class Systems {
    using SystemIndex = util::Index<unsigned long, ~0ul>;

    template <class System>
    class SystemMapping {
    public:
        static SystemIndex index;
    };

public:
    template <typename System, typename... Args>
    static bool create(Args&&... args)
    {
        if (!SystemMapping<System>::index.valid()) {
            SystemMapping<System>::index = createId();
            systems.emplace_back(new System(std::forward<Args>(args)...), [](void* system) {
                SystemMapping<System>::index.invalidate();
                delete static_cast<System*>(system);
            });
            return true;
        }
        return false;
    }

    template <typename System, typename Accessor>
    static bool with(Accessor&& accessor)
    {
        if (auto system = getSystem<System>()) {
            accessor(*system);
            return true;
        }
        return false;
    }

    static void reset()
    {
        systems.clear();
    }

private:
    template <typename System>
    static System* getSystem()
    {
        const auto index = SystemMapping<System>::index;
        if (index.valid() && index < systems.size()) {
            return static_cast<System*>(systems[index].get());
        }
        return nullptr;
    }

    static SystemIndex createId()
    {
        return SystemIndex{ systems.size() };
    }

    using SystemsContainer = std::vector<std::unique_ptr<void, void (*)(void*)>>;

    static SystemsContainer systems;
};

template <class System>
Systems::SystemIndex Systems::SystemMapping<System>::index = Systems::SystemIndex();
}

