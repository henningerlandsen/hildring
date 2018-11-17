#include "util/LifetimeTokenStack.h"

namespace util {

LifetimeTokenStack::~LifetimeTokenStack()
{
    std::for_each(stack.rbegin(), stack.rend(), [](LifetimeToken& token) {
        token.release();
    });
}

void LifetimeTokenStack::push(LifetimeToken&& token)
{
    stack.push_back(std::move(token));
}
}
