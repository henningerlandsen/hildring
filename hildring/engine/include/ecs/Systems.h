#pragma once

#include <memory>
#include <vector>

namespace ecs {
class Systems {
    using SystemId = int;

    class BaseSystemContainer {
    public:
        virtual ~BaseSystemContainer() = default;
    };

    template <class System, typename... Args>
    class SystemContainer : public BaseSystemContainer {
    public:
        explicit SystemContainer(Args&&... args)
            : system(std::forward<Args>(args)...)
        {
            //            if (id == -1) {
            //                id = getNextId();
            //            }
        }

        System& getSystem()
        {
            return system;
        }

        //        static getSystemId() const { return id; }

    private:
        System system;
        //        static SystemId id = -1;
    };

public:
    template <typename System, typename... Args>
    static void addComponentSystem(Args&&... args)
    {
        systems.emplace_back(new SystemContainer<System, Args...>(std::forward<Args>(args)...));
    }

    template <typename System>
    static System& getSystem()
    {
        return static_cast<SystemContainer<System>*>(systems[systems.size() - 1].get())->getSystem();
    }

private:
    using SystemContainers = std::vector<std::unique_ptr<BaseSystemContainer>>;

    static SystemContainers systems;
};

Systems::SystemContainers Systems::systems = Systems::SystemContainers();
}
