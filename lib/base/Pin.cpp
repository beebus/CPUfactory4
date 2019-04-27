// Copyright 2018 Roie R. Black
#include "Pin.h"
#include "Component.h"

// constructor
Pin::Pin(std::string n) {
    name = n;
    val = 42;
}

// mutators
void Pin::set_val(uint16_t v) {
    val = v;
}

void Pin::set_part_addr(Component * p) {
    part_addr = p;
}

// accessors
uint16_t Pin::get_val(void) {
    return val;
}

std::string Pin::get_name(void) {
    return name;
}

std::string Pin::get_part_name(void) {
    return part_addr->get_name();
}

