#pragma once
#include "container.hpp"

namespace nd {
class LayoutRow : public nd::Container {
public:
    LayoutRow() : nd::Container() {}
    std::unique_ptr<nd::Widget> clone() const override {
        return std::make_unique<nd::LayoutRow>();
    }

    void build() override; // HEAD@build
};
}
