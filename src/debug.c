#include "wm.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

GC default_gc;
int i = 0;

void init_debug_gc(Display *dpy, Window win) {
    default_gc = XCreateGC(dpy, win, 0, NULL);
    XSetForeground(dpy, default_gc, 0xff0000);
}

void show_debug_info(Display *dpy, Window win, char *info) {
    char buf[256] = {0};
    snprintf(buf, sizeof(buf), "DEBUG %d: %s", i, info);
    i++;

    unsigned int screen_height = DisplayHeight(dpy, DefaultScreen(dpy));

    XSetForeground(dpy, default_gc, 0xFFFFFF);
    XFillRectangle(dpy, win, default_gc, 0, screen_height - 20, 200, 20);
    XSetForeground(dpy, default_gc, 0xFF0000);
    XDrawString(dpy, win, default_gc, 10, screen_height - 10, buf, strlen(buf));
}
