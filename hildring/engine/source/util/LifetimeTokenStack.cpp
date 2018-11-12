#include "util/LifetimeTokenStack.h"

namespace util {

LifetimeTokenStack::~LifetimeTokenStack()
{
    while (!stack.empty()) {
        stack.erase(stack.end() - 1);
    }
}

void LifetimeTokenStack::push(LifetimeToken&& token)
{
    stack.push_back(std::move(token));
}
}
