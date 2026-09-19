#pragma once
#include "container.hpp"

namespace nd {
class LayoutColumn : public nd::Container {
public:
    LayoutColumn() : nd::Container() {}
    std::unique_ptr<nd::Widget> clone() const override {
        return std::make_unique<nd::LayoutColumn>();
    }

    void build() override; // HEAD@build
};
}
