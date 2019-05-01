// Copyright 2019 Roie R. Black
#include "Source.h"
#include <iostream>
#include <string>

// constructor
Source::Source(std::string n):Component(n) {
    this->add_out_pin("OUT");
    val = 0;
}

// TICK: perform component processing
void Source::tick(int ctrl) {
    Pin *outpin = this->get_out_pin("OUT");
    if (outpin) {
        outpin->set_val(val);
    }
}

void Source::set_val(uint16_t v) {
    val = v;
}


