#pragma once

#include <memory>
#include <vector>

namespace ecs {

class System {
    class ComponentWrapperBase {
    public:
        virtual ~ComponentWrapperBase() = default;
    };

    template <class T, typename... Args>
    class ComponentWrapper : public ComponentWrapperBase {
    public:
        ComponentWrapper(Args... args)
            : component(args...)
        {
        }

    private:
        T component;
    };

public:
    template <typename ComponentT, typename... Args>
    void addComponentHandler(Args... args)
    {
        m_component = std::make_unique<ComponentWrapper<ComponentT, Args...>>(std::forward<Args>(args)...);
    }

private:
    std::unique_ptr<ComponentWrapperBase> m_component;
};
}
