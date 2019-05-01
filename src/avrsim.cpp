// Copyright 2019 Roie R. Black
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "glui.h"
#include "GLUI_SevenSeg.h"
#include "GLUI_Led.h"
#include "version.h"
#include "AVRsim.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

std::string version = "AVRsim (";
char app_name[50];

#define PC_INCREMENT    200
#define PC_RESET        201
#define PC_ID           300
#define INS1_ID         301
#define INS2_ID         302
#define PCN_ID          303
#define ALUOP_ID        304
#define RD_ID           305
#define RS_ID           306
#define K_ID            307
#define A_ID            308

// "live" variables accessed by graphics routines
int   last_x, last_y;
int   main_window;
int  _pc = 0;
int _counter = 0;
int _ins1 = 0;
int _ins2 = 0;
int _aluop = 0;
int _pcn = 0;
int _rd = 0;
int _rs = 0;
int _k = 0;
int _a = 0;


// This is the primary graphics object
GLUI *glui;
AVRsim * sim;

// control routine called when we click the mouse on a control
void control_cb(int control) {
    if (control == PC_INCREMENT) {
        int stage = _pc % 4;
        switch (stage) {
            case 0: sim->fetch(); break;
            case 1: sim->decode(); break;
            case 2: sim->execute(); break;
            case 3: sim->store(); break;
        }
        _pc = sim->tick(_pc);
        // fetch signals
        _ins1 = sim->get_signal_by_name("ins1");
        _ins2 = sim->get_signal_by_name("ins2");
        // decode signals
        _pcn = sim->get_signal_by_name("pcn");
        _rd = sim->get_signal_by_name("rd");
        _rs = sim->get_signal_by_name("rs");
        _k = sim->get_signal_by_name("k");
        _a = sim->get_signal_by_name("a");
    } else if (control == PC_RESET) {
        _pc = 0;
    }
}

// user keyboard handler
void myGlutKeyboard(unsigned char Key, int x, int y) {
    switch(Key) {
        case 27:
            case 'q':
            exit(0);
            break;
    };
    glutPostRedisplay();
}

// called when no other events need processing in the graphics loop
void myIdleFunction(void) {
    if (glutGetWindow() != main_window)
        glutSetWindow(main_window);
    _counter++;
    glui->sync_live();      // update display of "live variables"
    glutPostRedisplay();
}

// User mouse handler
void myGlutMouse(int button, int button_state, int x, int y ) {
    if ( button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN ) {
        last_x = x;
        last_y = y;
    }
}

// draw the current screen - most work is behind the scenes
void myGlutDisplay() {
    glClearColor( .9f, .9f, .9f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glutSwapBuffers();
}


int main(int argc, char* argv[]) {
    version +=  VERSION;
    version +=  ")";
    std::strcpy(app_name, version.c_str()); 
    
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );

    // create the top-level window and position it on the screen
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(485, 530);

    // create graphics window
    main_window = glutCreateWindow(app_name);

    // register the user functions
    glutDisplayFunc(myGlutDisplay);
    glutKeyboardFunc( myGlutKeyboard );
    glutMouseFunc( myGlutMouse );

    // create GUI panel subwindow in the main window
    glui = GLUI_Master.create_glui_subwindow(
        main_window, GLUI_SUBWINDOW_TOP);

    // add controls to subwindow
    new GLUI_StaticText( glui, "Controls" );
    new GLUI_SevenSeg( glui, "SevenSeg" );
    new GLUI_Separator( glui );
    GLUI_EditText *counter_edittext =
        new GLUI_EditText(glui, "Count:", &_counter);

    new GLUI_Button( glui, "Step", PC_INCREMENT, control_cb);
    new GLUI_Button( glui, "Reset", PC_RESET, control_cb);
    new GLUI_Button( glui, "Quit", 0,(GLUI_Update_CB)exit );

    // set up machine display area
    GLUI_Panel * machine = new GLUI_Panel(glui, "Machine");
    GLUI_Panel * fetch_panel = new GLUI_Panel(machine, "Fetch");
    new GLUI_EditText(fetch_panel, "PC",
         GLUI_EDITTEXT_INT,
         &_pc, PC_ID, control_cb);
    new GLUI_EditText(fetch_panel, "Ins1",
         GLUI_EDITTEXT_INT,
         &_ins1, INS1_ID, control_cb);
    new GLUI_EditText(fetch_panel, "Ins2",
         GLUI_EDITTEXT_INT,
         &_ins2, INS2_ID, control_cb);

    GLUI_Panel * decode_panel = new GLUI_Panel(machine, "Decode");
    new GLUI_EditText(decode_panel, "ALUop",
         GLUI_EDITTEXT_INT,
         &_aluop, ALUOP_ID, control_cb);
    new GLUI_EditText(decode_panel, "PC+1",
         GLUI_EDITTEXT_INT,
         &_pcn, PCN_ID, control_cb);
    new GLUI_EditText(decode_panel, "Rd",
         GLUI_EDITTEXT_INT,
         &_rd, RD_ID, control_cb);
    new GLUI_EditText(decode_panel, "Rs",
         GLUI_EDITTEXT_INT,
         &_rs, RD_ID, control_cb);
    new GLUI_EditText(decode_panel, "K",
         GLUI_EDITTEXT_INT,
         &_k, RD_ID, control_cb);
    new GLUI_EditText(decode_panel, "A",
         GLUI_EDITTEXT_INT,
         &_a, RD_ID, control_cb);

    new GLUI_Column(machine,true);
    GLUI_Panel * execute_panel = new GLUI_Panel(machine, "Execute");
    GLUI_Panel * store_panel = new GLUI_Panel(machine, "Store");

    new GLUI_Column(machine,true);
    
    GLUI_Panel * segdisp = new GLUI_Panel(machine, "SevenSeg");
    new GLUI_SevenSeg(segdisp, "7Seg1");
    new GLUI_Column(segdisp,false);
    new GLUI_SevenSeg(segdisp, "7Seg2");

    GLUI_Panel * leddisp = new GLUI_Panel(machine, "Leds");
    new GLUI_Led(leddisp, "Led1");
    new GLUI_Column(leddisp,false);
    new GLUI_Led(leddisp, "Led2");
    new GLUI_Column(leddisp,false);
    new GLUI_Led(leddisp, "Led3");
    new GLUI_Column(leddisp,false);
    new GLUI_Led(leddisp, "Led4");

    glui->set_main_gfx_window(main_window);
    GLUI_Master.set_glutIdleFunc(myIdleFunction);
    sim = new AVRsim;
    if (sim) {
        sim->set_debug();
        sim->builder("data/avrsim.net");
    }
    glutMainLoop();
    return EXIT_SUCCESS;
}
