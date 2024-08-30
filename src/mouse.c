#include "mouse.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

GC mouse_gc;

void init_mouse_gc(Display *dpy, Window win) {
    mouse_gc = XCreateGC(dpy, win, 0, NULL);
    XSetForeground(dpy, mouse_gc, 0x000000);
}

void draw_cursor(Display *dpy, Window win, int x, int y) {
    XFillRectangle(dpy, win, mouse_gc, x-7, y-1, 6, 2);
    XFillRectangle(dpy, win, mouse_gc, x-1, y-7, 2, 6);

    XFillRectangle(dpy, win, mouse_gc, x+1, y-1, 6, 2);
    XFillRectangle(dpy, win, mouse_gc, x-1, y+1, 2, 6);
}
