// Copyright 2019 Roie R. Black
#pragma once
#include <string>
#include <cstdint>
#include "Component.h"

class Source : public Component {
 public:
    // constructors
    explicit Source(std::string n);

    // mutators
    void tick(int ctrl);
    void set_val(uint16_t v);

 private:
    uint16_t val;
};
