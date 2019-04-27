// Copyright 2018 Roie R. Black
#include "Wire.h"

// constructors
Wire::Wire(std::string n) {
    name = n;
    driven = nullptr;
}

// accessors
std::string Wire::get_name(void) {
    return name;
}

std::string Wire::get_driven_name(void) {
    if (driven)
        return driven->get_name();
    return "no attachment";
}

std::string Wire::get_driven_part_name(void) {
    if (driven)
        return driven->get_part_name();
    return "UNK";
}

std::string Wire::get_drives_names(void) {
    std::string names = "";
    for (int i = 0; i < drives.size(); i++) {
        if (i > 0) names += " ";
        names += drives[i]->get_name();
    }
    return names;
}

std::string Wire::get_drives_part_name(int i) {
    return drives[0]->get_part_name();
}

uint16_t Wire::get_val(void) {
    return val;
}

// mutators
void Wire::tock(void) {
    val = driven->get_val();
    for (int i = 0; i < drives.size(); i++) {
        drives[i]->set_val(val);
    }
}

void Wire::attach_driven(Pin * pin) {
    driven = pin;
}

void Wire::attach_drives(Pin * pin) {
    drives.push_back(pin);
}



