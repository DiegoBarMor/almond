#pragma once
#include "container.hpp"

namespace nd {
class LayoutColumn : public Container {
public:
    LayoutColumn() : Container() {}
    std::unique_ptr<Widget> clone() const override {
        return std::make_unique<LayoutColumn>();
    }

    void build() override; // HEAD@build
};
}
