// Copyright 2019 Roie R. Black
#pragma once
#include <glui.h>

class GLUI_SevenSeg : public GLUI_Control {
 public:
    void draw(int x, int y);

    GLUI_SevenSeg(GLUI_Node *parent, const GLUI_String &name);
    GLUI_SevenSeg() { common_init(); }
    void set_hex_digit(int n);
    void set_decimal_digit(int n);
    void set_on(int obits);
    void set_off(void);

 protected:
    void common_init();

 private:
    int bar;
    int bits;
    void drawSeg(void);
    void drawFilledSeg(void);
    void drawHbar(int hoff, int voff, bool on);
    void drawVbar(int hoff, int voff, bool on);
    void drawSegA(bool on);
    void drawSegB(bool on);
    void drawSegC(bool on);
    void drawSegD(bool on);
    void drawSegE(bool on);
    void drawSegF(bool on);
    void drawSegG(bool on);
    void drawSegDot(bool on);
    void drawCircle(int x, int y, int r);    
    void drawFilledCircle(int x, int y, int r);    
    int w;
    int h;
};

