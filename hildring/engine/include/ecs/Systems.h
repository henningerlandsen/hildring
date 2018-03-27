#pragma once

#include <assert.h>
#include <memory>
#include <vector>

namespace ecs {
class Systems {
    using SystemId = size_t;
    static const SystemId InvalidId;

    class BaseSystemContainer {
    public:
        virtual ~BaseSystemContainer() = default;
    };

    template <class System>
    class SystemContainer : public BaseSystemContainer {
    public:
        template <typename... Args>
        explicit SystemContainer(SystemId _id, Args&&... args)
            : system(std::forward<Args>(args)...)
        {
            assert(id == InvalidId);
            id = _id;
        }

        ~SystemContainer()
        {
            id = InvalidId;
        }

        System& getSystem()
        {
            return system;
        }

        static SystemId getId()
        {
            return id;
        }

    private:
        System system;
        static SystemId id;
    };

public:
    template <typename System, typename... Args>
    static bool addComponentSystem(Args&&... args)
    {
        if (SystemContainer<System>::getId() == InvalidId) {
            const auto id = createId();
            systems.emplace_back(new SystemContainer<System>(id, std::forward<Args>(args)...));
            return true;
        }
        return false;
    }

    template <typename System>
    static System* getSystem()
    {
        const auto id = SystemContainer<System>::getId();
        if (id != InvalidId && id < systems.size()) {
            return &static_cast<SystemContainer<System>*>(systems[id].get())->getSystem();
        }
        return nullptr;
    }

    static void reset()
    {
        systems.clear();
    }

private:
    static SystemId createId()
    {
        return SystemId{ systems.size() };
    }

    using SystemContainers = std::vector<std::unique_ptr<BaseSystemContainer>>;

    static SystemContainers systems;
};

Systems::SystemContainers Systems::systems = Systems::SystemContainers();
const Systems::SystemId Systems::InvalidId = -1;

template <class System>
Systems::SystemId Systems::SystemContainer<System>::id = Systems::InvalidId;
}

