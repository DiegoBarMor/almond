#pragma once
#include "container.hpp"

namespace nd {
class LayoutRow : public Container {
public:
    LayoutRow() : Container() {}
    std::unique_ptr<Widget> clone() const override {
        return std::make_unique<LayoutRow>();
    }

    void build() override; // HEAD@build
};
}
