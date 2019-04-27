//#include "glui_internal_control.h"
#include "GLUI_Led.h"
#include "tinyformat.h"
#include <cmath>

const double PI = acos(-1.0);
const double ANGLE_STEP      = PI / 180.0;

#define NOT !
#define LED_WIDTH 20
#define LED_HEIGHT 20

GLUI_Led::GLUI_Led( GLUI_Node *parent, const GLUI_String &name)
{
  common_init();
  set_name( name );

  parent->add_control( this );
}

void GLUI_Led::common_init() 
{
  name         = tfm::format("Led: %p", this);
  h            = LED_HEIGHT;
  w            = LED_WIDTH;
  alignment    = GLUI_ALIGN_CENTER;
  can_activate = true;
}

void    GLUI_Led::draw( int x, int y )
{
    glui->draw_raised_box( 0, 0, w, h );
    drawFilledCircle(w / 2, h / 2, w / 2 - 2);
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

