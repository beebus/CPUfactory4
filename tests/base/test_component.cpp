// Copyright 2018 Roie R. Black
#include <catch.hpp>
#include "Component.h"
#include "Pin.h"

TEST_CASE("test component constructor", "component"){
    const std::string name = "basic";
    Component part(name);
    REQUIRE(part.get_name() == name);
}

TEST_CASE("test component pin attachment", "component") {
    const std::string pname1 = "PIN1";
    const std::string pname2 = "PIN2";
    const std::string cname = "comp1";
    Component part(cname);
    part.add_in_pin(pname1);
    part.add_in_pin(pname2);
    part.get_in_pin(pname1)->set_val(2);
    part.get_in_pin(pname2)->set_val(3);
    REQUIRE(part.get_in_pin(pname1)->get_val() == 2);
    REQUIRE(part.get_in_pin(pname2)->get_val() == 3);
    part.add_out_pin(pname1);
    part.add_out_pin(pname2);
    part.get_out_pin(pname1)->set_val(5);
    part.get_out_pin(pname2)->set_val(6);
    REQUIRE(part.get_out_pin(pname1)->get_val() == 5);
    REQUIRE(part.get_out_pin(pname2)->get_val() == 6);
}
