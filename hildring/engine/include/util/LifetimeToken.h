#pragma once

#include <functional>

namespace util {
class [[nodiscard]] LifetimeToken {
    public:
        LifetimeToken();
        LifetimeToken(std::function<void()> expirationCallback);
        ~LifetimeToken();

        LifetimeToken(const LifetimeToken& other) = delete;
        LifetimeToken& operator=(const LifetimeToken& other) = delete;

        LifetimeToken(LifetimeToken && other);
        LifetimeToken& operator=(LifetimeToken&& other);

        operator bool() const;

    private:
        std::function<void()> callback;
};
}
