// Copyright 2018 ROie R. Black
#include <catch.hpp>
#include "Pin.h"

const std::string name = "basic";

TEST_CASE( "test pin constructor", "pin" ){
    Pin pin(name);
    REQUIRE(pin.get_name() == name);
    REQUIRE(pin.get_val() == 42);
}

TEST_CASE( "test_pin set/get methods", "pin" ) {
    Pin pin(name);
    // new pins have a value of 42
    REQUIRE(pin.get_val() == 42);
    pin.set_val(1234);
    REQUIRE(pin.get_val() == 1234);
}

