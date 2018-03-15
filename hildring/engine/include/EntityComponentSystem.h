#pragma once

#include <memory>
#include <vector>

namespace ecs {

class System {
    class ComponentWrapperBase {
    public:
        virtual ~ComponentWrapperBase() = default;
    };

    template <class T>
    class ComponentWrapper : public ComponentWrapperBase {
    public:
        ComponentWrapper(std::unique_ptr<T> component)
            : component(std::move(component))
        {
        }

    private:
        std::unique_ptr<T> component;
    };

public:
    template <typename ComponentT, typename... Args>
    void addComponentHandler(Args... args)
    {
        auto component = std::make_unique<ComponentT>(std::forward<Args>(args)...);
        m_component = std::make_unique<ComponentWrapper<ComponentT>>(std::move(component));
    }

private:
    std::unique_ptr<ComponentWrapperBase> m_component;
};
}
