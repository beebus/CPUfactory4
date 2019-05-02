// Copyright 2019 Roie R. Black
#include "IM.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

// constructor
IM::IM(std::string n):Component(n) {
    this->add_in_pin("PC");
    this->add_out_pin("INS1");
    this->add_out_pin("INS2");
    mem = new uint16_t[500];
    endpgm = 0;
}

// load - load hex file
void IM::load(std::string fn) {
    std::string line;
    std::fstream fin;
    unsigned int nbytes;

    // open file and parse lines
    fin.open(fn);
    if (fin) {
        while (!fin.eof()) {
            fin >> line;
            int len = line.size();

            std::string bytes = line.substr(1, 2);
            nbytes = std::stoul(bytes, nullptr, 16);
            std::string offset = line.substr(3, 4);
            unsigned int addr = std::stoul(offset, nullptr, 16);
            unsigned maddr = addr / 2;
            std::string record = line.substr(7, 2);
            std::string data = line.substr(9, len - 11);
            std::string check = line.substr(len - 2, 2);
            if (!(record == "00")) continue;
            for (int i=0; i < nbytes; i += 2) {
                std::string byte1 = data.substr(i*2, 2);
                std::string byte2 = data.substr(i*2+2, 2);
                std::string word = byte2 + byte1;
                unsigned val = std::stoul(word, nullptr, 16);
                mem[maddr++] = val;
                addr +=2;
            }
            endpgm = maddr;
        }
    }
}

// TICK: perform component processing
void IM::tick(int ctrl) {
    Pin *pcpin = this->get_in_pin("PC");
    Pin *ins1pin = this->get_out_pin("INS1");
    Pin *ins2pin = this->get_out_pin("INS2");

    uint16_t pc = pcpin->get_val();
    //std::cout << "Tick pc: " << pc << std::endl;
    uint16_t ins1 = mem[pc];
    //std::cout << "Tick ins1: " << ins1 << std::endl;
    uint16_t ins2 = mem[pc+1];

    pc = get_pin_val(pcpin);
    set_pin_val(ins1pin, mem[pc]);
    set_pin_val(ins2pin, mem[pc+1]);
}

void IM::dump(void) {
    for (int i=0; i< endpgm; i++) {
        std::cout << std::bitset<16>(mem[i]) << std::endl;
    }
}

uint16_t IM::get_val(uint16_t addr) {
    if (addr < endpgm) return mem[addr];
    return 0;
}

uint16_t IM::size(void) {
    return endpgm;
}


