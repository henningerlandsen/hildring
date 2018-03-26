#pragma once

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
        explicit SystemContainer(Args&&... args)
            : system(std::forward<Args>(args)...)
        {
        }

        ~SystemContainer()
        {
            id = InvalidId;
        }

        System& getSystem()
        {
            return system;
        }

    private:
        System system;
        static SystemId id;

        friend class Systems;
    };

public:
    template <typename System, typename... Args>
    static bool addComponentSystem(Args&&... args)
    {
        if (SystemContainer<System>::id == InvalidId) {
            SystemContainer<System>::id = systems.size();
            systems.emplace_back(new SystemContainer<System>(std::forward<Args>(args)...));
            return true;
        }
        return false;
    }

    template <typename System>
    static System& getSystem()
    {
        return static_cast<SystemContainer<System>*>(
            systems[systems.size() - 1].get())
            ->getSystem();
    }

    static void reset()
    {
        systems.clear();
    }

private:
    using SystemContainers = std::vector<std::unique_ptr<BaseSystemContainer>>;

    static SystemContainers systems;
};

Systems::SystemContainers Systems::systems = Systems::SystemContainers();
const Systems::SystemId Systems::InvalidId = -1;

template <class System>
Systems::SystemId Systems::SystemContainer<System>::id = Systems::InvalidId;
}

