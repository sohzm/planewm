#pragma once

#include <X11/Xlib.h>

void init_debug_gc(Display *dpy, Window win);
void show_debug_info(Display *dpy, Window win, char *info);
