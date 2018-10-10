#include "util/LifetimeToken.h"

namespace util {
LifetimeToken::LifetimeToken(std::function<void()> expirationCallback)
    : callback(expirationCallback)
{
}

LifetimeToken::LifetimeToken() {}

LifetimeToken::LifetimeToken(LifetimeToken&& other)
    : callback(std::move(other.callback))
{
    other.callback = nullptr;
}

LifetimeToken::~LifetimeToken()
{
    if (callback) {
        callback();
    }
}

LifetimeToken::operator bool() const
{
    return callback != nullptr;
}
}
