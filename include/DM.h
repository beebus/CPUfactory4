// Copyright 2018 Roie R. Black
#pragma once
#include <string>
#include <cstdint>
#include "Component.h"

class DM : public Component {
 public:
    // constructors
    explicit DM(std::string n);

    // mutators
    void tick(int ctrl);

 private:
    uint16_t val;
};
