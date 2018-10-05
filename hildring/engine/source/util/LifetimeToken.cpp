#include "util/LifetimeToken.h"

namespace util {
LifetimeToken::LifetimeToken(std::function<void()> expirationCallback)
    : callback(expirationCallback)
{
}

LifetimeToken::~LifetimeToken()
{
    callback();
}
}
