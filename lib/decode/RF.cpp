// Copyright 2018 Roie R. Black
#include "RF.h"
#include <iostream>
#include <string>

// constructor
RF::RF(std::string n):Component(n) {
    this->add_in_pin("RD");
    this->add_in_pin("RR");
    this->add_in_pin("MDR");
    this->add_out_pin("CRD");
    this->add_out_pin("CRR");
}

// TICK: perform component processing
void RF::tick(int ctrl) {
}
