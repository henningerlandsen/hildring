#include "util/LifetimeTokenStack.h"

#include <algorithm>

namespace util {

void LifetimeTokenStack::push(LifetimeToken&& token)
{
    stack.push_back(std::move(token));
}
}
