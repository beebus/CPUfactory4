// Copyright 2018 Roie R. Black
#include <catch.hpp>
#include "MUX2.h"
#include "alu_ops.h"

std::string MNAME = "CPUtest";
MUX2 mux(MNAME);

TEST_CASE("test MUX2 constructor", "parts") {
    REQUIRE(mux.get_name() == MNAME);
}

TEST_CASE( "test_MUX2 selector operation", "parts" ) {
    Pin * in1pin = mux.get_in_pin("IN1");
    Pin * in2pin = mux.get_in_pin("IN2");
    Pin * outpin = mux.get_out_pin("OUT");
    in1pin->set_val(1);
    in2pin->set_val(2);
    mux.tick(0);
    REQUIRE(outpin->get_val() == 1);
    mux.tick(1);
    REQUIRE(outpin->get_val() == 2);
}
