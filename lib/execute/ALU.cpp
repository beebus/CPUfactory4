// Copyright 2018 Roie R. Black
#include <iostream>
#include <string>
#include "ALU.h"
#include "alu_ops.h"

// constructor
ALU::ALU(std::string n):Component(n) {
    this->add_in_pin("IN1");
    this->add_in_pin("IN2");
    this->add_in_pin("AOP");
    this->add_out_pin("RES8");
    this->add_out_pin("RES16");
    val = 0;
}

// TICK: perform component processing
void ALU::tick(int ctrl) {
    Pin *in1pin = this->get_in_pin("IN1");
    Pin *in2pin = this->get_in_pin("IN2");
    Pin *out1pin = this->get_out_pin("RES8");
    Pin *out2pin = this->get_out_pin("RES16");
    uint16_t ival1, ival2, aop, oval;

    try {
        ival1 = in1pin->get_val();
        ival2 = in2pin->get_val();
        aop = ctrl;
    }
    catch (std::exception & e) {
        std::cout
            << "ALU pins not configured: "
            << e.what()
            << std::endl;
    }
    switch (aop) {
        case ADD:
            oval = ival1 + ival2;
            break;
        case SUB:
            oval = ival1 - ival2;
            break;
        case COM:
            oval = ~ival1;
            break;
        case AND:
            oval = ival1 & ival2;
            break;
        case OR:
            oval = ival1 | ival2;
            break;
        case EOR:
            oval = ival1 ^ ival2;
            break;
    }
    try {
        std::cout << "ALU: " << oval << std::endl;
        out1pin->set_val(oval);
    }
    catch(std::exception e) {
        std::cout
            << "ALU out pin not configured"
            << e.what()
            << std::endl;
    }
}
