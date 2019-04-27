// Copyright 2019 Roie R. Black
#pragma once

#include <cstdint>
#include <string>

class Component;

class Pin {
 public:
     // constructor
    explicit Pin(std::string n);

    // accessors
    uint16_t get_val(void);
    std::string get_name(void);
    std::string get_part_name(void);

    // mutators
    void set_val(uint16_t v);
    void set_part_addr(Component * p);

 private:
    std::string name;
    uint16_t val;
    Component * part_addr;
};

