// Copyright 2019 Roie R. Black
#include "AVRsim.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include "Source.h"
#include "Pin.h"
#include "MUX2.h"
#include "PC.h"
#include "IM.h"
#include "RF.h"
#include "IO.h"
#include "MUX4.h"
#include "DM.h"
#include "STK.h"
#include "ALU.h"
#include "Decoder.h"
#include "microcode.h"

AVRsim::AVRsim() {
    nparts = 0;
    nwires = 0;
    nucodes = 0;
    debug = false;
}

void AVRsim::set_debug(void) {
    debug = true;
}

uint16_t AVRsim::tick(uint16_t c) {
    pc = c;
    return ++pc;
}

void AVRsim::run_ucode(uCode * ucode) {
    if (ucode) {
        for (int i=0; i < ucode->uops.size(); i++) {
            uOp * uops = ucode->uops[i];
            std::cout 
                << "\t" 
                << uops->part->get_name()
                << "("
                << uops->ctrl
                << ")" 
                << std::endl;
        }
    }
}

void AVRsim::fetch(void) {
    std::cout << "Fetch" << std::endl;
    uCode * ucode = find_ucode("Fetch");
    run_ucode(ucode);
}

void AVRsim::decode(void) {
    std::cout << "decode" << std::endl;
    uCode * ucode = find_ucode("Decode");
    run_ucode(ucode);    
}

void AVRsim::execute(void) {
    std::cout << "execute" << std::endl;
    uCode * ucode = find_ucode("Execute");
    run_ucode(ucode);    
}

void AVRsim::store(void) {
    std::cout << "store" << std::endl;
    uCode * ucode = find_ucode("Store");
    run_ucode(ucode);    
}

Component * AVRsim::find_part(std::string part) {
        for (int i = 0; i < parts.size(); i++) {
            std::string tname = parts[i]->get_name();
            if (parts[i]->get_name() == part) return parts[i];
        }
        return nullptr;
}

Pin * AVRsim::find_pin(Component * part, std::string pname) {
    // check in_pins
    Pin * pin = part->get_in_pin(pname);
    if (pin) return pin;
    return part->get_out_pin(pname);
}

void AVRsim::attach_driven(Wire * w, std::string id) {
    int pos = id.find(".");
    std::string part, pin;
    part = id.substr(0, pos);
    pin = id.substr(pos+1, id.size());
    Component * part_ptr = find_part(part);
    if (!part_ptr) {
        std::cout << "part not found: " << part << std::endl;
        exit(1);
    }
    Pin * pin_ptr = find_pin(part_ptr, pin);
    if (!pin_ptr) {
        std::cout << part << "." << pin << " not found" << std::endl;
        exit(1);
    }
    w->attach_driven(find_pin(part_ptr, pin));
}

void AVRsim::attach_drives(Wire * w, std::string id) {
    int pos = id.find(".");
    std::string part, pin;
    part = id.substr(0, pos);
    pin = id.substr(pos+1, id.size());
    Component * part_ptr = find_part(part);
    if (!part_ptr) {
        std::cout << "part not found: " << part << std::endl;
        exit(1);
    }
    Pin * pin_ptr = find_pin(part_ptr, pin);
    if (!pin_ptr) {
        std::cout << part << "." << pin << " not found" << std::endl;
        exit(1);
    }
    w->attach_drives(find_pin(part_ptr, pin));
}


void AVRsim::builder(std::string fname) {
    std::ifstream fin;
    std::string token, name;
    int ctrl;

    std::cout <<
        "Building machine from: " 
        << fname 
        << std::endl;

    fin.open(fname);
    if (!fin) {
        std::cout 
            << "Cannot open machine def file: " 
            << fname 
            << std::endl;
        exit(1);
    }
    std::cout 
        << "Building machine"
        << std::endl;
    while (fin >> token) {
        std::cout 
            << token
            << std::endl;
        if (token == "PARTS") {
            while (true) {
                fin >> token;
                if (token == "END") break;
                fin >> name;
                nparts++;
                std::cout << "Building " << token << "(" << name << ")" << std::endl;
                if (token == "Source") {
                    Source * src_part = new Source(name);
                    parts.push_back(reinterpret_cast<Component *>(src_part));
                } else if (token == "MUX2") {
                    MUX2 * mux2_part = new MUX2(name);
                    parts.push_back(reinterpret_cast<Component *>(mux2_part));
                } else if (token == "MUX4") {
                    MUX4 * mux4_part = new MUX4(name);
                    parts.push_back(reinterpret_cast<Component *>(mux4_part));
                } else if (token == "PC") {
                    PC * pc_part = new PC(name);
                    parts.push_back(reinterpret_cast<Component *>(pc_part));
                } else if (token == "IM") {
                    IM * im_part = new IM(name);
                    parts.push_back(reinterpret_cast<Component *>(im_part));
                } else if (token == "DM") {
                    DM * dm_part = new DM(name);
                    parts.push_back(reinterpret_cast<Component *>(dm_part));
                } else if (token == "STK") {
                    STK * stk_part = new STK(name);
                    parts.push_back(reinterpret_cast<Component *>(stk_part));
                } else if (token == "Decoder") {
                    Decoder * dec_part = new Decoder(name);
                    parts.push_back(reinterpret_cast<Component *>(dec_part));
                } else if (token == "ALU") {
                    ALU * alu_part = new ALU(name);
                    parts.push_back(reinterpret_cast<Component *>(alu_part));
                } else if (token == "RF") {
                    RF * rf_part = new RF(name);
                    parts.push_back(reinterpret_cast<Component *>(rf_part));
                } else if (token == "IO") {
                    IO * io_part = new IO(name);
                    parts.push_back(reinterpret_cast<Component *>(io_part));
                } else {
                    Component * part = new Component(name);
                    parts.push_back(part);
                }

                std::cout << "Part: " << token << std::endl;
            }
        } else if (token == "WIRES") { 
                        if (debug)
                std::cout
                    << "Generating wires"
                    << std::endl;
            while (fin >> token) {
                if (token == "END") break;
                nwires++;
                Wire * new_wire = new Wire(token);
                wires.push_back(new_wire);
                // connect this wire
                if (debug)
                    std::cout
                        << "Wire: "
                        << token
                        <<std::endl;
                fin >> token;
                attach_driven(new_wire, token);
                if (debug)
                    std::cout
                        << "\tdriven by: "
                        << token
                        << std::endl;
                fin >> token;   // skip ->
                do {
                    fin >> token;   // drives
                    if (debug)
                        std::cout
                            << "\tdrives: "
                            << token
                            << std::endl;
                    attach_drives(new_wire, token);
                    fin >> token;   // comma or semicolon
                } while (token != ";");
            }
        } else if (token == "UCODE") {
            while (fin >> token) {
                if (token == "END") break;
                if (debug) 
                    std::cout
                        << "\tadding instruction: "
                        << token
                        << std::endl;
                uCode * new_ucode = new uCode;
                new_ucode->name = token;
                while (true) {
                    fin >> token;
                    if (token == ";") break;
                    if (debug) {
                        std::cout
                            << "\t\tadding uop: "
                            << token
                            << std::endl;
                    }
                    int pos = token.find(".");
                    std::string part = token.substr(0,pos);
                    std::string sctrl = token.substr(pos+1, token.size());
                    if (sctrl != "reset")
                        ctrl = std::stoi(sctrl);
                    else ctrl = 0;
                    if (debug)
                        std::cout
                            << "part: "
                            << part
                            << "("
                            << ctrl
                            << ")"
                            << std::endl;
                    uOp * new_uop = new uOp;
                    new_uop->part = find_part(part);
                    new_uop->ctrl = ctrl;
                    new_ucode->uops.push_back(new_uop);
                }
                ucodes.push_back(new_ucode);
            }
            if (debug)
                std::cout
                    << ucodes.size()
                    << " ucode blocks processed"
                    << std::endl;
        }
    }
    std::cout << "done!"
        << std::endl;
}

uint16_t AVRsim::get_signal_by_name(std::string n) {
    if (n == "pc")
        return 2;
    else if (n == "ins1")
        return 0x3f;
    else if (n == "ins2")
        return 0x004f;
    else if (n == "rd")
        return 0x005f;
    else if (n == "rs")
        return 0x006f;
    else if (n == "aluop")
        return 0x007f;
    else if (n == "k")
        return 0x008f;
    else if (n == "a")
        return 0x009f;
    else if (n == "ins2")
        return 0x00af;
    else return 0;
}

uCode * AVRsim::find_ucode(std::string name) {
    for (int i=0; i < ucodes.size(); i++) {
        uCode * ucode = ucodes[i];
        if (ucode->name == name) {
            return ucode;
        }
    }
    return nullptr;
}
