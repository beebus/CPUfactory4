// Copyright 2018 Roie R. Black
#pragma once
#include <string>
#include <cstdint>
#include "Component.h"

class STK : public Component {
 public:
    // constructors
    explicit STK(std::string n);

    // mutators
    void tick(int ctrl);

 private:
    uint16_t val;
};
