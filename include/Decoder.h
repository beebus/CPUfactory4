// Copyright 2019 Roie R> Black
#pragma once
#include <string>
#include "Component.h"

class Decoder : public Component {
 public:
    explicit Decoder(std::string name);
    void tick(int ctrl);
    int dump(uint16_t pc, uint16_t ins1, uint16_t ins2);

 private:
    std::string name;
    std::string mnemonic;
    uint16_t pc;
    uint16_t Rd;
    uint16_t Rr;
    uint16_t A;
    uint16_t k;
    uint16_t Aop;

    int decode(uint16_t pc, uint16_t ins1, uint16_t ins2);
};



