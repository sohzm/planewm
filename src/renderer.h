#pragma once

#include <X11/Xlib.h>

void render_screen(Display *dpy, Window win, GC gc, XEvent *ev);
void render_bar(Display *dpy, Window win, GC gc);
void render_windows(Display *dpy, Window win, GC gc);
