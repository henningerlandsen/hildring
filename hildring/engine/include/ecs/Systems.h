#pragma once

#include <memory>
#include <vector>

namespace ecs {
    class Systems {
        class BaseSystemContainer {
        public:
            virtual ~BaseSystemContainer() = default;
        };

        template <class System, typename... Args>
        class SystemContainer : public BaseSystemContainer {
        public:
            explicit SystemContainer(Args&&... args)
                    : system(args...)
            {
            }

        private:
            System system;
        };

    public:
        template <typename System, typename... Args>
        static void addComponentSystem(Args&&... args)
        {
            systems.emplace_back(new SystemContainer<System, Args...>(std::forward<Args>(args)...));
        }

    private:
        using SystemContainers = std::vector<std::unique_ptr<BaseSystemContainer>>;

        static SystemContainers systems;
    };

    Systems::SystemContainers Systems::systems = Systems::SystemContainers();
}

