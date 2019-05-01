// Copyright 2018 Roie R. Black
#include <catch.hpp>
#include "IM.h"

TEST_CASE("test IM constructor", "parts") {
    std::string NAME = "CPUtest";
    IM im(NAME);
    REQUIRE(im.get_name() == NAME);
}

TEST_CASE( "test_IM operation", "fetch") {
    std::string name = "IM";
    IM im(name);
    Pin * inpin = im.get_in_pin("PC");
    REQUIRE(inpin != nullptr);
    Pin * outpin1 = im.get_out_pin("INS1");
    REQUIRE(outpin1 != nullptr);
    Pin * outpin2 = im.get_out_pin("INS2");
    REQUIRE(outpin2 != nullptr);
    inpin->set_val(1);
    im.tick(0);
    REQUIRE(outpin1->get_val() == 0);
    im.tick(0);
    REQUIRE(outpin1->get_val() == 1);
}
