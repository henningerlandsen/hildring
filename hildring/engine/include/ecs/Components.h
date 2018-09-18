#pragma once

namespace ecs {
class Components {
public:
    template <typename System, typename Component>
    static bool add()
    {
        return true;
    }
};
}
