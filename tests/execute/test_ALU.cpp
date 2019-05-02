// Copyright 2018 Roie R. Black
#include <catch.hpp>
#include "ALU.h"
#include "alu_ops.h"

std::string NAME = "CPUtest";
ALU alu(NAME);
Pin * in1pin = alu.get_in_pin("IN1");
Pin * in2pin = alu.get_in_pin("IN2");
Pin * aoppin = alu.get_in_pin("AOP");
Pin * outpin = alu.get_out_pin("RES8");

TEST_CASE("test ALU constructor", "parts") {
    REQUIRE(alu.get_name() == NAME);
}

TEST_CASE( "test_ALU ADD operation", "parts" ) {
    in1pin->set_val(1);
    in2pin->set_val(2);
    aoppin->set_val(ADD);
    alu.tick(0);
    REQUIRE(outpin->get_val() == 3);
}

TEST_CASE( "test_ALU COM operation", "parts" ) {
    in1pin->set_val(0x00ff);
    aoppin->set_val(COM);
    alu.tick(0);
    REQUIRE(outpin->get_val() == 0xff00);
}

TEST_CASE( "test_ALU SUB operation", "parts" ) {
    in1pin->set_val(3);
    in2pin->set_val(1);
    aoppin->set_val(SUB);
    alu.tick(0);
    REQUIRE(outpin->get_val() == 2);
}

TEST_CASE( "test_ALU AND operation", "parts" ) {
    in1pin->set_val(0x1122);
    in2pin->set_val(0xff);
    aoppin->set_val(AND);
    alu.tick(0);
    REQUIRE(outpin->get_val() == 0x0022);
}

TEST_CASE( "test_ALU OR operation", "parts" ) {
    in1pin->set_val(0xff);
    in2pin->set_val(0xff00);
    aoppin->set_val(OR);
    alu.tick(0);
    REQUIRE(outpin->get_val() == 0xffff);
}

TEST_CASE( "test_ALU EOR operation", "parts" ) {
    in1pin->set_val(0xff);
    in2pin->set_val(0xff);
    aoppin->set_val(EOR);
    alu.tick(0);
    REQUIRE(outpin->get_val() == 0);
}
