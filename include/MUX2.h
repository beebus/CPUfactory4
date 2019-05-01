// COpyright 2019 Roie R. Black
#pragma once
#include <string>
#include "Component.h"

class MUX2 : public Component {
 public:
    explicit MUX2(std::string name);
    void tick(int ctrl);
};
