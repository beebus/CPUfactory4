// Copyright 2019 Roie R. Black
#include <glui.h>
#include "GLUI_SevenSeg.h"
#include "GLUI_Led.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// create the master GLUI object pointer
GLUI * glui;
int main_window;

void myGlutDisplay() {
    glClearColor(0.9f, .9f, .9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSwapBuffers();
}

void myGlutKeyboard(unsigned char Key, int x, int y) {
    switch(Key) {
        case 27:
        case 'q':
            exit(0);
            break;
    }
}

void myGlutIdle() {
    if (glutGetWindow() != main_window)
        glutSetWindow(main_window);

    glutPostRedisplay();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowPosition( 50, 50 ); glutInitWindowSize( 300, 300 );

    main_window = glutCreateWindow( "GLUI Example 3" );
    glutDisplayFunc( myGlutDisplay );
    glutKeyboardFunc( myGlutKeyboard );

    glui = GLUI_Master.create_glui( "GLUI", 0, 500, 100 );
    new GLUI_StaticText( glui, "GLUI Example 3" );
    new GLUI_Button(glui, "Quit", 0,(GLUI_Update_CB)exit );

    GLUI_Panel * segdisp = new GLUI_Panel(glui, "SevenSeg");
    new GLUI_SevenSeg(segdisp, "7Seg1");
    new GLUI_Column(segdisp,false);
    new GLUI_SevenSeg(segdisp, "7Seg2");

    GLUI_Panel * leddisp = new GLUI_Panel(glui, "Leds");
    new GLUI_Led(leddisp, "Led1");
    new GLUI_Column(leddisp,false);
    new GLUI_Led(leddisp, "Led2");
    new GLUI_Column(leddisp,false);
    new GLUI_Led(leddisp, "Led3");
    new GLUI_Column(leddisp,false);
    new GLUI_Led(leddisp, "Led4");


    glui->set_main_gfx_window( main_window );
    GLUI_Master.set_glutIdleFunc( myGlutIdle );

    glutMainLoop();

    return EXIT_SUCCESS;
}
