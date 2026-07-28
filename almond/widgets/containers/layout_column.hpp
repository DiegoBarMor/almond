#pragma once
#include "container.hpp"

namespace nd {
class LayoutColumn : public Container {
public:
    LayoutColumn() : Container() {}
    LayoutColumn* clone() override { return new LayoutColumn(); }

    void build() override; // HEAD@build
};
}
