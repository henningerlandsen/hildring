#pragma once

#include "util/LifetimeToken.h"

#include <vector>

namespace util {

class LifetimeTokenStack {
public:
    LifetimeTokenStack() = default;
    ~LifetimeTokenStack();

    LifetimeTokenStack(const LifetimeTokenStack&) = delete;
    LifetimeTokenStack& operator=(const LifetimeTokenStack&) = delete;

    LifetimeTokenStack(LifetimeTokenStack&&) = default;
    LifetimeTokenStack& operator=(LifetimeTokenStack&&) = default;

    void push(LifetimeToken&& token);

private:
    std::vector<util::LifetimeToken> stack;
};
}
