#pragma once
#include <glui.h>

class GLUI_Led : public GLUI_Control {
public:
    void draw(int x, int y) override;
    void draw_border(int x, int y);
    void drawFilledCircle(int x, int y, int radius);
    GLUI_Led(GLUI_Node *parent, const GLUI_String &name);
    GLUI_Led() { common_init(); }

protected:
    void common_init();
};

