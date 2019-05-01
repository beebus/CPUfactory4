// Copyright 2018 Roie R. Black
#pragma once
#include <string>
#include <cstdint>
#include "Component.h"

class IM : public Component {
 public:
    // constructors
    explicit IM(std::string n);

    // accessors
    void dump(void);
    uint16_t get_val(uint16_t addr);
    uint16_t size(void);

    // mutators
    void tick(int ctrl);
    void load(std::string fn);

 private:
    uint16_t * mem;
    unsigned int endpgm;
};
