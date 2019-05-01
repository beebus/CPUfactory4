// Copyright 2019 Roie R. Black
#include "Decoder.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

// constructor
Decoder::Decoder(std::string n):Component(n) {
    this->add_in_pin("PC");
    this->add_in_pin("INS1");
    this->add_in_pin("INS2");
    this->add_out_pin("PCN");
    this->add_out_pin("AOP");
    this->add_out_pin("RD");
    this->add_out_pin("RR");
    this->add_out_pin("K");
    this->add_out_pin("A");
}

// TICK: perform component processing
void Decoder::tick(int ctrl) {
    Pin *pcpin = this->get_in_pin("PC");
    Pin *ins1pin = this->get_in_pin("INS1");
    Pin *ins2pin = this->get_in_pin("INS2");
    pc = get_pin_val(pcpin);
    uint16_t ins1 = get_pin_val(ins1pin);
    uint16_t ins2 = get_pin_val(ins2pin);
    decode(pc, ins1, ins2);
}

int getRd(int n1, int n2) {
    std::bitset<4> b1(n1);
    std::bitset<4> b2(n2);
    std::bitset<5> Rd;
    Rd[4] = b1[1];
    Rd[3] = b2[3];
    Rd[2] = b2[2];
    Rd[1] = b2[1];
    Rd[0] = b2[0];
    return Rd.to_ulong();
}

int getRr(int n1, int n2) {
    std::bitset<4> b1(n1);
    std::bitset<4> b2(n2);
    std::bitset<5> Rr;
    Rr[4] = b1[0];
    Rr[3] = b2[3];
    Rr[2] = b2[2];
    Rr[1] = b2[1];
    Rr[0] = b2[0];
    return Rr.to_ulong();
}

template <typename T>
std::string hexify(T i) {
    std::stringbuf buf;
    std::ostream os(&buf);
    os << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2)
        << std::hex << i;
    return buf.str().c_str();
}

void display(int otype, std::string m, int op1, int op2) {
    std::cout << m;
    uint16_t ks;
    switch (otype) {
        case 0:     // no operands
            break;
        case 1:     // Rd
            std::cout << "\t"
                << "r" << op1;
            break;
        case 2:     // Rd, Rr
            std::cout << "\t"
                << "r" << op1
                << ","
                << "r" <<  op2;
            break;
        case 3:     // K,Rr
            ks = op1;
            std::cout << "\t"
                << hexify<uint16_t>(ks)
                << ","
                << "r" << op2;
            break;
        case 4:     // Rd, K
            ks = op2;
            std::cout << "\t"
                << "r" << op1
                << ","
                << hexify<uint16_t>(ks);
            break;
        case 5:     // A,b
            std::cout << "\t"
                << op1
                << ","
                << op2;
            break;
        case 6:     // K
            std::cout << "\t"
                << op1;
            break;
        case 7:     // K (signed)
            int32_t ks = op1 < 2048 ? op1 : op1 - 4096;
            std::cout << "\t"
                << ks;
            break;
    }
    std::cout << std::endl;
}


int Decoder::decode(uint16_t pc, uint16_t ins1, uint16_t ins2) {
    int N1, N2, N3, N4, b;
    std::bitset<6> A;
    int aint, kint;
    std::bitset<12> k12;
    std::string mnemonic;
    int bytes = 1;

    // break out nibbles from first instruction code
    N4 = (ins1 & 0x000f);
    N3 = ((ins1 >> 4) & 0x000f);
    N2 = ((ins1 >> 8) & 0x000f);
    N1 = (ins1 >> 12) & 0x000f;

    // get the nibble bitsets
    std::bitset<4> n1(N1);
    std::bitset<4> n2(N2);
    std::bitset<4> n3(N3);
    std::bitset<4> n4(N4);

    // display the breakout
    std::cout
        << pc
        << " -> ("
        << n1
        << ":" << n2
        << ":" << n3
        << ":" << n4
        << ") ";

    // decode based on four nibbles
    switch (N1) {
        case 0b0000:
            if (n2 == 0 && n3 == 0 && n4 == 0) {
                // NOP
                mnemonic = "nop";
                display(0, mnemonic, 0, 0);
            } else if (n2.test(3) && n2.test(2)) {
                // ADD
                mnemonic = "add";
                Rd = getRd(N2, N3);
                Rr = getRr(N2, N3);
                display(2, mnemonic, Rd, Rr);
            } else if (!n2.test(3) && n2.test(2)) {
                // CP
                mnemonic = "cp";
                Rd = getRd(N2, N3);
                Rr = getRr(N2, N3);
                display(2, mnemonic, Rd, Rr);
            } else if (n2.test(3) && !n2.test(2)) {
                // SBC
                mnemonic = "sbc";
                Rd = getRd(N2, N3);
                Rr = getRr(N2, N3);
                display(2, mnemonic, Rd, Rr);
            } else if (n2.test(3) && !n2.test(2)) {
                // SUB
                mnemonic = "sub";
                Rd = getRd(N2, N3);
                Rr = getRd(N2, N4);
                display(2, mnemonic, Rd, Rr);
            }
            break;
        case 0b0001:
            break;
        case 0b0010:
            if (!n2.test(3) && n2.test(2)) {
                // EOR
               mnemonic = "eor";
                Rd = getRd(N2, N3);
                Rr = getRr(N2, N4);
               display(2, mnemonic, Rd, Rr);
            } else if (!n2.test(3) && !n2.test(2)) {
                // AND
                mnemonic = "and";
                Rd = getRd(N2, N3);
                Rr = getRr(N2, N3);
                display(2, mnemonic, Rd, Rr);
            }
            break;
        case 0b0011:
            break;
        case 0b0100:
            break;
        case 0b0101:
            break;
        case 0b0110:
            break;
        case 0b0111:
            break;
        case 0b1000:
            break;
        case 0b1001:
        if (!n2.test(3) && !n2.test(2) && n2.test(1)) {
            if (N4 == 0) {
                // STS
                mnemonic = "sts";
                Rr = getRr(N2, N3);
                kint = ins2;
                display(3, mnemonic, kint, Rr);
                bytes++;
            } else if (N4 == 0b1111) {
                // PUSH
                mnemonic = "push";
                Rr = getRr(N2, N3);
                display(1, mnemonic, Rr, 0);
            }
        } else if ((N2 == 5) && (N3 == 0) && (N4 == 8)) {
                // RET
                mnemonic = "ret";
                display(0, mnemonic, 0, 0);
            } else if (((N2 >> 1) == 2) && (N4 == 10)) {
                // DEC
                mnemonic = "dec";
                Rd = getRr(N2, N3);
                display(1, mnemonic, Rd, 0);
            } else if (N2 == 10) {
                // SBI
                mnemonic = "sbi";
                aint = (N3  << 1) + (N4 >> 3);
                b = (N4 & 0b0111);
                display(5, mnemonic, aint, b);
            } else if (n2 == 8) {
                // CBI
                mnemonic = "cbi";
                aint = (N3  << 1) + (N4 >> 3);
                b = (N4 & 0b0111);
                display(5, mnemonic, aint, b);
            }
            break;
        case 0b1010:
            break;
        case 0b1011:
            aint = (((N2 >> 1) & 0b0011) << 4) + N4;
            if (!n2.test(3)) {
                // IN
                mnemonic = "in";
                Rd = getRr(N2, N3);
                display(4, mnemonic, Rd, aint);
            } else {
                // OUT
                mnemonic = "out";
                Rr = getRr(N2, N3);
                display(3, mnemonic, aint, Rr);
            }
            break;
        case 0b1100:
            // RJMP
            mnemonic = "rjmp";
            kint = (N2 << 8) + (N3 << 4) + N4;
            k12 = kint;
            display(7, mnemonic, kint, 0);
            break;
        case 0b1101:
            // RCALL
            mnemonic = "rcall";
            kint = (N2 << 8) + (N3 << 4) + N4;
            display(6, mnemonic, kint, 0);
            break;
        case 0b1110:
            // LDI
            mnemonic = "ldi";
            kint = (N2 << 4) + N4;
            Rd = N3 + 16;
            display(4, mnemonic, Rd, kint);
            break;
        case 0b1111:
            if (((N2 >> 2) == 1) && ((N4 & 0b0111) == 1)) {
                // BRNE
                mnemonic = "brne";
                kint = ((N2 & 0b0011) << 5) +
                    (N3 << 1) + (N4 >> 3);
                display(7, mnemonic, kint, 0);
            }
            break;
    }
    return bytes;
}

int Decoder::dump(uint16_t pc, uint16_t ins1, uint16_t ins2) {
    return decode(pc, ins1, ins2);
}

