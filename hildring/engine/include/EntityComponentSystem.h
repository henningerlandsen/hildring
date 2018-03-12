#pragma once

#include <memory>
#include <vector>

namespace ecs {

class System {
public:
    template <typename ComponentHanderT, typename... Args>
    void addComponentHandler(Args... args)
    {
        std::make_unique<ComponentHanderT>(std::forward<Args>(args)...);
    }

private:
};
}
