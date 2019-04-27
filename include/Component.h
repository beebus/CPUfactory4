// Copyright 2018 Roie R. Black
#pragma once

#include <string>
#include <vector>

#include "Component.h"
#include "Pin.h"


class Component {
 public:
    bool debug;
    // constructor
    explicit Component(std::string n);

    // mutators
    void add_in_pin(std::string name);
    void add_out_pin(std::string name);
    void tick(int ctrl);
    void set_pin_val(Pin * p, uint16_t val);
    void set_debug(void);

    // accessors
    std::string get_name(void);
    Pin * get_in_pin(std::string n);
    Pin * get_out_pin(std::string n);
    uint16_t get_pin_val(Pin * p);
    void dump(void);

 private:
    std::string name;
    std::vector<Pin *> in_pins;
    std::vector<Pin *> out_pins;
};

