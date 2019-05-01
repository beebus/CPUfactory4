// Copyright 2018 Roie R. Black
#include "IO.h"
#include <iostream>
#include <string>

// constructor
IO::IO(std::string n):Component(n) {
    this->add_in_pin("IN");
    this->add_in_pin("MAR");
    this->add_out_pin("OUT");
}

// TICK: perform component processing
void IO::tick(int ctrl) {
}
