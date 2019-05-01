// Copyright 2018 Roie R. Black
#include "DM.h"
#include <iostream>
#include <string>

// constructor
DM::DM(std::string n):Component(n) {
    this->add_in_pin("MAR");
    this->add_in_pin("IN");
    this->add_out_pin("OUT");
}

// TICK: perform component processing
void DM::tick(int ctrl) {
}
