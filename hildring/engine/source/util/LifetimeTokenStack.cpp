#include "util/LifetimeTokenStack.h"

namespace util {

LifetimeTokenStack::~LifetimeTokenStack()
{
    while (!stack.empty()) {
        stack.pop_back();
    }
}

void LifetimeTokenStack::push(LifetimeToken&& token)
{
    stack.push_back(std::move(token));
}
}
