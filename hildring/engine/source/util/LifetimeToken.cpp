#include "util/LifetimeToken.h"

namespace util {
LifetimeToken::LifetimeToken(std::function<void()> expirationCallback)
    : callback(expirationCallback)
{
}

LifetimeToken::LifetimeToken() {}

LifetimeToken::~LifetimeToken()
{
    release();
}

LifetimeToken::LifetimeToken(LifetimeToken&& other)
    : callback(std::move(other.callback))
{
    other.callback = nullptr;
}

LifetimeToken&
LifetimeToken::operator=(LifetimeToken&& other)
{
    if (this != &other) {
        release();
        std::swap(callback, other.callback);
    }
    return *this;
}

LifetimeToken::operator bool() const
{
    return callback != nullptr;
}

void LifetimeToken::release()
{
    if (callback) {
        callback();
        callback = nullptr;
    }
}
}
