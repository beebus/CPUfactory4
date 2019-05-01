// Copyright 2018 ROie R. Black
#include <catch.hpp>
#include "Pin.h"
#include "Wire.h"

TEST_CASE( "test wire constructor", "wire" ){
    const std::string name = "basic";
    Wire wire(name);
    REQUIRE(wire.get_name() == name);
}

TEST_CASE( "test wire operation", "wire" ) {
    Wire wire("W1");
    Pin pin1("P1");
    Pin pin2("P2");
    Pin pin3("P3");
    wire.attach_driven(&pin1);
    wire.attach_drives(&pin2);
    wire.attach_drives(&pin3);
    pin1.set_val(1234);
    wire.tock();
    REQUIRE(pin2.get_val() == 1234);
    REQUIRE(pin3.get_val() == 1234);
}

