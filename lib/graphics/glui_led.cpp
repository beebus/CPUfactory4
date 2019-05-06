// Copyright 2019 Roie R. Black
//#include "glui_internal_control.h"
#include "GLUI_Led.h"
#include <cmath>

const double PI = acos(-1.0);
const double ANGLE_STEP      = PI / 180.0;

#define NOT !
#define LED_SIZE 20
#define MARGIN 2

GLUI_Led::GLUI_Led(GLUI_Node *parent, const GLUI_String &name) {
    common_init();
    set_name( name );
    led_on = false;

    parent->add_control( this );
}

void GLUI_Led::common_init() {
    name         = "led";
    h            = LED_SIZE;
    w            = LED_SIZE;
    alignment    = GLUI_ALIGN_CENTER;
    can_activate = true;
}

void GLUI_Led::draw(int x, int y) {
    int center = w / 2;
    glui->draw_raised_box( 0, 0, w, h );
    if (led_on) drawFilledCircle(center, center, center -  MARGIN);
    else drawCircle(center, center, center - MARGIN);
}

void GLUI_Led::drawFilledCircle(int x, int y, int radius) {
     double angle;
     int X0, Y0, X1, Y1;
     glColor3f( 1.0, 0.0, 0.0 );
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
void GLUI_Led::drawCircle(int x, int y, int radius) {
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

void GLUI_Led::set(bool on) {
    led_on = on;
}

