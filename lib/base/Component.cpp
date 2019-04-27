// Copyright 2018 Roie R. Black
#include <iostream>
#include "Component.h"
#include "Pin.h"

// constructors
Component::Component(std::string n) {
    name = n;
}

// accessor methods

std::string Component::get_name(void) {
    return name;
}

Pin * Component::get_in_pin(std::string name) {
    for (int i = 0; i < in_pins.size(); i++) {
        if (debug)
            std::cout
                << "in: "
                << in_pins[i]->get_name()
                << std::endl;
        if (in_pins[i]->get_name() == name) return in_pins[i];
    }
    return nullptr;
}

Pin * Component::get_out_pin(std::string name) {
    for (int i = 0; i < out_pins.size(); i++) {
        if (debug)
            std::cout
                << "out: "
                << out_pins[i]->get_name()
                << std::endl;
        if (out_pins[i]->get_name() == name) return out_pins[i];
    }
    return nullptr;
}

// mutator methods

void Component::set_debug(void) {
    debug = true;
}

void Component::add_in_pin(std::string name) {
    Pin * paddr = new Pin(name);
    paddr->set_val(42);
    paddr->set_part_addr(this);
    in_pins.push_back(paddr);
}

void Component::add_out_pin(std::string name) {
    Pin * paddr = new Pin(name);
    paddr->set_val(42);
    paddr->set_part_addr(this);
    out_pins.push_back(paddr);
}

uint16_t Component::get_pin_val(Pin * p) {
    uint16_t val = 0;
    try {
        val = p->get_val();
    }
    catch (std::exception & e) {
        std::cout
            << "pins not configured ("
            << p->get_name()
            << ") "
            << e.what()
            << std::endl;
    }
    return val;
}

void Component::set_pin_val(Pin * p, uint16_t val) {
    try {
        p->set_val(val);
    }
    catch (std::exception & e) {
        std::cout
            << "output pin not configured ("
            << p->get_name()
            << ") "
            << e.what()
            << std::endl;
    }
}

void Component::dump(void) {
    std::cout << name << ":" << std::endl;
    for (int i = 0; i < in_pins.size(); i++) {
        std::cout
            << "\tin" << i
            << in_pins[i]->get_val()
            << std::endl;
    }
    for (int i = 0; i < out_pins.size(); i++) {
        std::cout
            << "\tout" << i
            << " " << out_pins[i]->get_name()
            << out_pins[i]->get_val()
            << std::endl;
    }
}

void Component::tick(int ctrl) {}
