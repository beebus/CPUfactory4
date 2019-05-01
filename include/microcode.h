// Copyright 2019 Roie R. Black
#pragma once
#include <string>
#include <vector>
#include "Component.h"

struct uOp {
    Component * part;
    int ctrl;
};

struct uCode {
    std::string name;
    std::vector<uOp *>uops;
};

