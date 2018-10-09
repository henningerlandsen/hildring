#pragma once

#include <functional>

namespace util {
class [[nodiscard]] LifetimeToken {
    public:
        LifetimeToken(std::function<void()> expirationCallback);
        LifetimeToken();
        ~LifetimeToken();

        LifetimeToken(const LifetimeToken& other) = delete;
        LifetimeToken(LifetimeToken && other);

        operator bool() const;

    private:
        std::function<void()> callback;
};
}
