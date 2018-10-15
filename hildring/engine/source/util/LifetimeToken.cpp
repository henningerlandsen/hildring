#include "util/LifetimeToken.h"

namespace util {
LifetimeToken::LifetimeToken(std::function<void()> expirationCallback)
    : callback(expirationCallback)
{
}

LifetimeToken::LifetimeToken() {}

LifetimeToken::~LifetimeToken()
{
    if (callback) {
        callback();
    }
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
        if (callback) {
            callback();
        }
        callback = other.callback;
        other.callback = nullptr;
    }
    return *this;
}

LifetimeToken::operator bool() const
{
    return callback != nullptr;
}
}
