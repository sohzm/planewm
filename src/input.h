#pragma once

#include <X11/Xlib.h>

void handle_button_press_event(Display *dpy, XEvent *ev);
void handle_key_press_event(Display *dpy, XEvent *ev);
void handle_event(Display *dpy, Window win, GC gc, XEvent *ev);
