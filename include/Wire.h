// Copyright 2018 Roie R. Black
#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include "Pin.h"


class Wire {
 public:
    // constructors
    explicit Wire(std::string n);

    // accessors
    std::string get_name(void);
    std::string get_driven_part_name(void);
    std::string get_drives_part_name(int i);
    std::string get_driven_name(void);
    std::string get_drives_names(void);
    uint16_t get_val(void);

    // mutators
    void tock();
    void attach_drives(Pin * pin);
    void attach_driven(Pin * pin);

 private:
    std::string name;
    uint16_t val;
    Pin *driven;
    std::vector<Pin *> drives;
};

