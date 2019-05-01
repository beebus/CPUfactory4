// COpyright 2019 Roie R. Black
#pragma once
#include <string>
#include "Component.h"

class MUX4 : public Component {
 public:
    explicit MUX4(std::string name);
    void tick(int ctrl);
};
