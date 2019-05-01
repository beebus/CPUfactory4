// Copyright 2019 Roie R. Black
#include <iostream>
#include "MUX2.h"

MUX2::MUX2(std::string n):Component(n) {
    this->add_in_pin("IN1");
    this->add_in_pin("IN2");
    this->add_in_pin("SEL");
    this->add_out_pin("OUT");
}

void MUX2::tick(int ctrl) {
    if (debug)
        std::cout
            << "MUX2 tick("
            << ctrl
            << ")"
            << std::endl;

    Pin *in1pin = this->get_in_pin("IN1");
    Pin *in2pin = this->get_in_pin("IN2");
    Pin *outpin = this->get_out_pin("OUT");
    uint16_t ival1, ival2, oval;

    try {
        ival1 = in1pin->get_val();
        ival2 = in2pin->get_val();
    }
    catch (std::exception & e) {
        std::cout
            << "MUX2 pins not configured: "
            << e.what()
            << std::endl;
    }

    //  selector logic
    if (ctrl)
        oval = ival2;
    else
        oval = ival1;

    //  record result
    try {
        outpin->set_val(oval);
    }
    catch(std::exception e) {
        std::cout
            << "ALU out pin not configured"
            << e.what()
            << std::endl;
    }
}
