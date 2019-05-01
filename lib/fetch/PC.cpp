// Copyright 2018 Roie R. Black
#include "PC.h"
#include <iostream>
#include <string>

// constructor
PC::PC(std::string n):Component(n) {
    this->add_in_pin("IN");
    this->add_out_pin("OUT");
    val = 0;
}

// TICK: perform component processing
void PC::tick(int ctrl) {
    Pin *inpin = this->get_in_pin("IN");
    Pin *outpin = this->get_out_pin("OUT");
    uint16_t ival, oval;

    oval = val;
    if (inpin) {
        val = inpin->get_val();
    }
    if (outpin) {
        outpin->set_val(oval);
    }
}

