#pragma once

#include <X11/Xlib.h>

void set_window_manager_property(Display *dpy, Window win, const char *property, const char *value);
void handle_expose_event(Display *dpy, Window win, GC gc);
void handle_map_request_event(Display *dpy, XEvent *ev);
void handle_configure_request_event(Display *dpy, XEvent *ev);
