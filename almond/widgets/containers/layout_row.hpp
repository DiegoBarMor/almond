#pragma once
#include "container.hpp"

namespace nd {
class LayoutRow : public Container {
public:
    LayoutRow() : Container() {}
    LayoutRow* clone() override { return new LayoutRow(); }

    void build() override; // HEAD@build
};
}
