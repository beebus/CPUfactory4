// Copyright 2019 Roie R. Black
#include <iostream>
#include "MUX4.h"

MUX4::MUX4(std::string n):Component(n) {
    this->add_in_pin("IN1");
    this->add_in_pin("IN2");
    this->add_in_pin("IN3");
    this->add_in_pin("SEL");
    this->add_out_pin("OUT");
}

void MUX4::tick(int ctrl) {
    Pin *in1pin = this->get_in_pin("IN1");
    Pin *in2pin = this->get_in_pin("IN2");
    Pin *in3pin = this->get_in_pin("IN3");
    Pin *in4pin = this->get_in_pin("IN4");
    Pin *outpin = this->get_out_pin("OUT");
    uint16_t ival1, ival2, ival3, ival4, oval;

    try {
        ival1 = in1pin->get_val();
        ival2 = in2pin->get_val();
        ival3 = in3pin->get_val();
        ival4 = in4pin->get_val();
    }
    catch (std::exception & e) {
        std::cout
            << "MUX4 pins not configured: "
            << e.what()
            << std::endl;
    }

    //  selector logic
    if (ctrl == 0) {
        oval = ival1;
    } else {
        if (ctrl == 1)
            oval = ival2;
        else
            oval = ival3;
    }

    //  record result
    try {
        outpin->set_val(oval);
    }
    catch(std::exception e) {
        std::cout
            << "MUX4 out pin not configured"
            << e.what()
            << std::endl;
    }
}
