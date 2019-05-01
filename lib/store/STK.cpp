// Copyright 2018 Roie R. Black
#include "STK.h"
#include <iostream>
#include <string>

// constructor
STK::STK(std::string n):Component(n) {
    this->add_in_pin("IN");
    this->add_out_pin("OUT");
}

// TICK: perform component processing
void STK::tick(int ctrl) {
}
