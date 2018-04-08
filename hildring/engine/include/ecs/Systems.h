#pragma once

#include <assert.h>
#include <memory>
#include <vector>

namespace ecs {
class Systems {
    using SystemIndex = size_t;
    static const SystemIndex InvalidIndex;

    template <class System>
    class SystemMapping {
    public:
        static SystemIndex index;
    };

public:
    template <typename System, typename... Args>
    static bool addSystem(Args&&... args)
    {
        if (SystemMapping<System>::index == InvalidIndex) {
            SystemMapping<System>::index = createId();
            systems.emplace_back(new System(std::forward<Args>(args)...), [](void* system) {
                SystemMapping<System>::index = InvalidIndex;
                delete static_cast<System*>(system);
            });
            return true;
        }
        return false;
    }

    template <typename System>
    static System* getSystem()
    {
        const auto index = SystemMapping<System>::index;
        if (index != InvalidIndex && index < systems.size()) {
            return static_cast<System*>(systems[index].get());
        }
        return nullptr;
    }

    static void reset()
    {
        systems.clear();
    }

private:
    static SystemIndex createId()
    {
        return SystemIndex{ systems.size() };
    }

    using SystemsContainer = std::vector<std::unique_ptr<void, void (*)(void*)>>;

    static SystemsContainer systems;
};

Systems::SystemsContainer Systems::systems = Systems::SystemsContainer();
const Systems::SystemIndex Systems::InvalidIndex = -1;

template <class System>
Systems::SystemIndex Systems::SystemMapping<System>::index = Systems::InvalidIndex;
}

