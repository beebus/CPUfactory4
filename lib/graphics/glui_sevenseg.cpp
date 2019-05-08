// Copyright 2019 Roie R. Black
#include "GLUI_SevenSeg.h"
#include <cmath>
#include <iostream>


const double PI = acos(-1.0);
const double ANGLE_STEP      = PI / 180.0;
const int MARGIN = 3;
const int BAR = 10;

#define NOT !
#define SEG_WIDTH 80
#define SEG_HEIGHT 90

int hex_digit[16] = {
    0b00111111,     // 0
    0b00000110,     // 1
    0b01011011,     // 2
    0b01001111,     // 3
    0b01100110,     // 4
    0b01101101,     // 5
    0b01111101,     // 6
    0b00000111,     // 7
    0b01111111,     // 8
    0b01100111,     // 9
    0b01110111,     // A
    0b01111100,     // B
    0b00111001,     // C
    0b01011110,     // D
    0b01111001,     // E
    0b01110001      // F
};

int pos[6][2];

GLUI_SevenSeg::GLUI_SevenSeg(GLUI_Node *parent, const GLUI_String &name) {
    common_init();
    set_name(name);
    bits = 0b11111111;

    parent->add_control(this);
}

void GLUI_SevenSeg::common_init() {
  name          = "SevenSeg";
  h             = SEG_HEIGHT;
  w             = SEG_WIDTH;
  alignment     = GLUI_ALIGN_CENTER;
  can_activate  = false;
}

void GLUI_SevenSeg::draw(int x, int y) {
    glui->draw_raised_box(0, 0, w, h);
    bool ca, cb, cc, cd, ce, cf, cg, cdot;
    ca = (bits & 0b00000001) > 0;
    cb = (bits & 0b00000010) > 0;
    cc = (bits & 0b00000100) > 0;
    cd = (bits & 0b00001000) > 0;
    ce = (bits & 0b00010000) > 0;
    cf = (bits & 0b00100000) > 0;
    cg = (bits & 0b01000000) > 0;
    cdot = (bits & 0b10000000) > 0;

    drawSegA(ca);
    drawSegB(cb);
    drawSegC(cc);
    drawSegD(cd);
    drawSegE(ce);
    drawSegF(cf);
    drawSegG(cg);
    drawSegDot(cdot);
}

// mutators
void GLUI_SevenSeg::set_hex_digit(int n) {
    n = (n % 16);
    set_on(hex_digit[n]);
}

void GLUI_SevenSeg::set_decimal_digit(int n) {
    n = (n % 10);
    set_on(hex_digit[n]);
}


void GLUI_SevenSeg::set_on(int obits) {
    bits = obits;
}

void GLUI_SevenSeg::set_off(void) {
    bits = 0b00000000;
}

// private utility routines
void GLUI_SevenSeg::drawSeg(void) {
    glColor3f(0.0, 0.0, 0.0);
    int xs1 = pos[0][0];
    int ys1 = pos[0][1];
    int xs2 = pos[1][0];
    int ys2 = pos[1][1];
    int xs3 = pos[2][0];
    int ys3 = pos[2][1];
    int xs4 = pos[3][0];
    int ys4 = pos[3][1];
    int xs5 = pos[4][0];
    int ys5 = pos[4][1];
    int xs6 = pos[5][0];
    int ys6 = pos[5][1];
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2i(xs1, ys1);
    glVertex2i(xs2, ys2);
    glVertex2i(xs3, ys3);
    glVertex2i(xs4, ys4);
    glVertex2i(xs5, ys5);
    glVertex2i(xs6, ys6);
    glVertex2i(xs1, ys1);
    glEnd();
}

void GLUI_SevenSeg::drawFilledSeg(void) {
    int xs1 = pos[0][0];
    int ys1 = pos[0][1];
    int xs2 = pos[1][0];
    int ys2 = pos[1][1];
    int xs3 = pos[2][0];
    int ys3 = pos[2][1];
    int xs4 = pos[3][0];
    int ys4 = pos[3][1];
    int xs5 = pos[4][0];
    int ys5 = pos[4][1];
    int xs6 = pos[5][0];
    int ys6 = pos[5][1];
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(xs1, ys1);
    glVertex2i(xs2, ys2);
    glVertex2i(xs3, ys3);
    glVertex2i(xs4, ys4);
    glVertex2i(xs5, ys5);
    glVertex2i(xs6, ys6);
    glVertex2i(xs1, ys1);
    glEnd();
}

void GLUI_SevenSeg::drawHbar(int hoff, int voff, bool on) {
    int wbar = w - 2 * MARGIN - BAR;
    int x1 = 0;
    int x2 = BAR / 2;
    int x3 = wbar - BAR / 2;
    int x4 = wbar;
    int x5 = x3;
    int x6 = x2;
    int y1 = 0;
    int y2 = BAR / 2;
    int y3 = y2;
    int y4 = y1;
    int y5 = - BAR / 2;
    int y6 = y5;
    pos[0][0] = x1 + hoff;
    pos[0][1] = y1 + voff;
    pos[1][0] = x2 + hoff;
    pos[1][1] = y2 + voff;
    pos[2][0] = x3 + hoff;
    pos[2][1] = y3 + voff;
    pos[3][0] = x4 + hoff;
    pos[3][1] = y4 + voff;
    pos[4][0] = x5 + hoff;
    pos[4][1] = y5 + voff;
    pos[5][0] = x6 + hoff;
    pos[5][1] = y6 + voff;
    if (on)
        drawFilledSeg();
    else
        drawSeg();
}

void GLUI_SevenSeg::drawVbar(int hoff, int voff, bool on) {
    int hbar = h / 2 - MARGIN - BAR / 2;
    int x1 = 0;
    int x2 = BAR / 2;
    int x3 = x2;
    int x4 = 0;
    int x5 = -BAR / 2;
    int x6 = x5;
    int y1 = 0;
    int y2 = BAR / 2;
    int y3 = hbar - BAR / 2;;
    int y4 = hbar;
    int y5 = y3;
    int y6 = y2;
    pos[0][0] = x1 + hoff;
    pos[0][1] = y1 + voff;
    pos[1][0] = x2 + hoff;
    pos[1][1] = y2 + voff;
    pos[2][0] = x3 + hoff;
    pos[2][1] = y3 + voff;
    pos[3][0] = x4 + hoff;
    pos[3][1] = y4 + voff;
    pos[4][0] = x5 + hoff;
    pos[4][1] = y5 + voff;
    pos[5][0] = x6 + hoff;
    pos[5][1] = y6 + voff;
    if (on)
        drawFilledSeg();
    else
        drawSeg();
}

void GLUI_SevenSeg::drawSegA(bool on) {
    drawHbar(MARGIN + BAR / 2, MARGIN + BAR / 2, on);
}

void GLUI_SevenSeg::drawSegB(bool on) {
    drawVbar(w - MARGIN - BAR / 2, BAR / 2, on);
}

void GLUI_SevenSeg::drawSegC(bool on) {
    drawVbar(w - MARGIN - BAR / 2, h / 2, on);
}

void GLUI_SevenSeg::drawSegD(bool on) {
    drawHbar(MARGIN + BAR / 2, h - MARGIN - BAR / 2, on);
}


void GLUI_SevenSeg::drawSegE(bool on) {
    drawVbar(MARGIN + BAR / 2, h / 2, on);
}

void GLUI_SevenSeg::drawSegF(bool on) { drawVbar(MARGIN + BAR / 2, MARGIN + BAR
        / 2, on); }

void GLUI_SevenSeg::drawSegG(bool on) {
    drawHbar(MARGIN + BAR / 2, h / 2, on);
}


void GLUI_SevenSeg::drawSegDot(bool on) {
    int xd =  w - BAR / 2 - MARGIN;
    int yd = h - BAR / 2 - MARGIN;
    if (on)
        drawFilledCircle(xd, yd, BAR / 2);
    else
        drawCircle(xd, yd, BAR / 2);
}
void GLUI_SevenSeg::drawFilledCircle(int x, int y, int radius) {
     double angle;
     int X0, Y0, X1, Y1;
     glColor3f(1.0, 0.0, 0.0);
     glBegin(GL_TRIANGLES);
     X1 = x + radius;
     Y1 = y;
     for (angle = 0; angle < 2.0 * PI + ANGLE_STEP; angle += ANGLE_STEP) {
         X0 = X1;
         Y0 = Y1;
         X1 = x + static_cast<int>(static_cast<double>(radius) * cos(angle));
         Y1 = y + static_cast<int>(static_cast<double>(radius) * sin(angle));
         glVertex2i(x, y);
         glVertex2i(X0, Y0);
         glVertex2i(X1, Y1);
     }
     glEnd();
}

void GLUI_SevenSeg::drawCircle(int x, int y, int radius) {
     double angle;
     int X, Y;
     glBegin(GL_LINE_STRIP);
     for (angle = 0; angle < 2.0 * PI + ANGLE_STEP; angle += ANGLE_STEP) {
         X = x + static_cast<int>(static_cast<double>(radius) * cos(angle));
         Y = y + static_cast<int>(static_cast<double>(radius) * sin(angle));
         glVertex2i(X, Y);
     }
     glEnd();
}


