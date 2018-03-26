#pragma once

#include <memory>
#include <vector>

namespace ecs {
class Systems {
    using SystemId = size_t;

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

        System& getSystem()
        {
            return system;
        }

        static int getSystemId() { return id; }

    private:
        System system;
        static int id;

        friend class Systems;
    };

public:
    template <typename System, typename... Args>
    static void addComponentSystem(Args&&... args)
    {
        if (SystemContainer<System>::id == -1) {
            SystemContainer<System>::id = systems.size();
            systems.emplace_back(new SystemContainer<System>(std::forward<Args>(args)...));
        }
    }

    template <typename System>
    static System& getSystem()
    {
        return static_cast<SystemContainer<System>*>(
            systems[systems.size() - 1].get())
            ->getSystem();
    }

private:
    using SystemContainers = std::vector<std::unique_ptr<BaseSystemContainer>>;

    static SystemContainers systems;
};

Systems::SystemContainers Systems::systems = Systems::SystemContainers();

template <class System>
int Systems::SystemContainer<System>::id = -1;
}

