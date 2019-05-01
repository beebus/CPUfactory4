// Copyright 2018 Roie R. Black
#pragma once
#include <string>
#include <cstdint>
#include "Component.h"

class IO : public Component {
 public:
    // constructors
    explicit IO(std::string n);

    // mutators
    void tick(int ctrl);

 private:
    uint16_t val;
};
