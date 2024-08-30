#pragma once

#include <X11/Xlib.h>

typedef struct WindowNode {
    Window id;
    int x, y;
    unsigned int width, height;
    char *title;
    struct WindowNode *next;
} WindowNode;

extern WindowNode *window_list;

void add_window(Display *dpy, Window id);
void remove_window(Display *dpy, Window id);
void focus_window(Display *dpy, Window id);
void raise_window(Display *dpy, Window id);
void update_window_list(Display *dpy);
void handle_window_events(Display *dpy, XEvent *ev);
