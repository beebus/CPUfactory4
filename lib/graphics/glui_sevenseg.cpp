//#include "glui_internal_control.h"
#include "GLUI_SevenSeg.h"
#include "tinyformat.h"

#define NOT !
#define SEG_WIDTH 80
#define SEG_HEIGHT 90

GLUI_SevenSeg::GLUI_SevenSeg( GLUI_Node *parent, const GLUI_String &name)
{
  common_init();
  set_name( name );

  parent->add_control( this );
}

void GLUI_SevenSeg::common_init() 
{
  name         = tfm::format("SevenSeg: %p", this);
  h            = SEG_HEIGHT;
  w            = SEG_WIDTH;
  alignment    = GLUI_ALIGN_CENTER;
  can_activate = true;
}

void    GLUI_SevenSeg::draw( int x, int y )
{
    glui->draw_raised_box( 0, 0, w, h );
}
