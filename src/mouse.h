#pragma once

#include <X11/Xlib.h>

void init_mouse_gc(Display *dpy, Window win);
void draw_cursor(Display *dpy, Window win, int x, int y);
