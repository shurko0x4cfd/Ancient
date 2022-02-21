
/* Alexander (Shurko) Stadnichenko */
/* Public domain */

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>

main () {

Display  *display;

static int attributes [] = {
    GLX_RGBA,
    GLX_DOUBLEBUFFER,
    GLX_RED_SIZE, 8,
    GLX_GREEN_SIZE, 8,
    GLX_BLUE_SIZE, 8,
    GLX_DEPTH_SIZE, 16,
    0 };

XVisualInfo *vinfo;

Window window;

XSetWindowAttributes winattrs;

int winmask;

GLXContext context;

display = XOpenDisplay(getenv("DISPLAY"));
if (display == NULL) printf("display == NULL/n");

vinfo = glXChooseVisual(display, DefaultScreen(display), attributes);
if (vinfo == NULL) printf("vinfo == NULL/n");

winattrs.event_mask   = ExposureMask | VisibilityChangeMask | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask ;
winattrs.border_pixel = 0;
winattrs.bit_gravity  = StaticGravity;
winmask               = CWEventMask | CWBorderPixel | CWBitGravity;

window = XCreateWindow (display, DefaultRootWindow(display), 0, 0, 400, 400, 0, vinfo->depth, InputOutput, CopyFromParent, winmask, &winattrs);

XChangeProperty (display, window, XA_WM_NAME,      XA_STRING, 8, 0, "GL", strlen("Asdf") );
XChangeProperty (display, window, XA_WM_ICON_NAME, XA_STRING, 8, 0, "Asdf", strlen("Asdf") );

XMapWindow(display, window);

context = glXCreateContext(display, vinfo, 0, True);

glXMakeCurrent(display, window, context);

glClearColor(1, 1, 0, 1);
/* glEnable(GL_DEPTH_TEST); */
glEnable(GL_CULL_FACE);

glViewport(0, 0, 400, 400);
glClear(GL_COLOR_BUFFER_BIT);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

glOrtho(-200, 200, -200, 200, -200, 200);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(200, 200, 0);
glEnd();

glXSwapBuffers(display, window);

for(;;){

glViewport(0, 0, 400, 400);
glClearColor(0, 0.5, 0, 1);
glClear(GL_COLOR_BUFFER_BIT);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-200, 200, -200, 200, -200, 200);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(200, 200, 0);
glEnd();

glXSwapBuffers(display, window);
}; /* for */

glXDestroyContext(display, context);

}
