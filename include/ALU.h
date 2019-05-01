// Copyright 2018 Roie R. Black
#pragma once
#include <string>
#include <cstdint>
#include "Component.h"

class ALU : public Component {
 public:
    // constructors
    explicit ALU(std::string n);

    // mutators
    void tick(int ctrl);
 private:
    uint16_t val;
};
