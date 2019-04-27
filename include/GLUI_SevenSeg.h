#pragma once
#include <glui.h>

class GLUI_SevenSeg : public GLUI_Control {
public:
    void draw(int x, int y) override;
    void draw_border(int x, int y);

    GLUI_SevenSeg(GLUI_Node *parent, const GLUI_String &name);
    GLUI_SevenSeg() { common_init(); }

protected:
    void common_init();
};

