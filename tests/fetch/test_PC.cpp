// Copyright 2018 Roie R. Black
#include <catch.hpp>
#include "PC.h"

TEST_CASE("test PC constructor", "parts") {
    std::string NAME = "CPUtest";
    PC pc(NAME);
    REQUIRE(pc.get_name() == NAME);
}

TEST_CASE( "test_PC operation", "parts" ) {
    std::string name = "PC";
    PC pc(name);
    Pin * inpin = pc.get_in_pin("IN");
    Pin * outpin = pc.get_out_pin("OUT");
    inpin->set_val(1);
    pc.tick(0);
    REQUIRE( outpin->get_val() == 0 );
    pc.tick(0);
    REQUIRE( outpin->get_val() == 1 );
}
