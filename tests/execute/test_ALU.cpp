// Copyright 2018 Roie R. Black
#include <catch.hpp>
#include "ALU.h"
#include "alu_ops.h"

std::string NAME = "CPUtest";
ALU alu(NAME);
Pin * in1pin = alu.get_in_pin("IN1");
Pin * in2pin = alu.get_in_pin("IN2");
Pin * outpin = alu.get_out_pin("RES8");

TEST_CASE("test ALU constructor", "parts") {
    REQUIRE(alu.get_name() == NAME);
}

TEST_CASE( "test_ALU ADD operation", "parts" ) {
    in1pin->set_val(1);
    in2pin->set_val(2);
    alu.tick(ADD);
    REQUIRE(outpin->get_val() == 3);
}

TEST_CASE( "test_ALU COM operation", "parts" ) {
    in1pin->set_val(0x00ff);
    alu.tick(COM);
    REQUIRE(outpin->get_val() == 0xff00);
}

TEST_CASE( "test_ALU SUB operation", "parts" ) {
    in1pin->set_val(3);
    in2pin->set_val(1);
    alu.tick(SUB);
    REQUIRE(outpin->get_val() == 2);
}

TEST_CASE( "test_ALU AND operation", "parts" ) {
    in1pin->set_val(0x1122);
    in2pin->set_val(0xff);
    alu.tick(AND);
    REQUIRE(outpin->get_val() == 0x0022);
}

TEST_CASE( "test_ALU OR operation", "parts" ) {
    in1pin->set_val(0xff);
    in2pin->set_val(0xff00);
    alu.tick(OR);
    REQUIRE(outpin->get_val() == 0xffff);
}

TEST_CASE( "test_ALU EOR operation", "parts" ) {
    in1pin->set_val(0xff);
    in2pin->set_val(0xff);
    alu.tick(EOR);
    REQUIRE(outpin->get_val() == 0);
}
