#include "renderer.h"
#include "debug.h"
#include "mouse.h"
#include "window.h"

#include "x11.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string.h>

struct window {
    int x;
    int y;
    int width;
    int height;
    char *title;
};

#define MAX_WINDOWS 100
struct window windows[MAX_WINDOWS] = {0};

void render_screen(Display *dpy, Window win, GC gc, XEvent *ev) {
    XClearWindow(dpy, win);
    render_bar(dpy, win, gc);
    render_windows(dpy, win, gc); // Add this line
    show_debug_info(dpy, win, "Hello, world!");
    if (ev->type == MotionNotify) {
        draw_cursor(dpy, win, ev->xmotion.x, ev->xmotion.y);
    }
    XFlush(dpy);
}

void render_bar(Display *dpy, Window win, GC gc) {
    int screen_num = DefaultScreen(dpy);
    unsigned int screen_width = DisplayWidth(dpy, screen_num);

    XSetForeground(dpy, gc, 0x000000);
    XFillRectangle(dpy, win, gc, 0, 0, screen_width, 30);

    XSetForeground(dpy, gc, 0xFFFFFF);
    XFillRectangle(dpy, win, gc, 10, 10, 120, 20);
    XFillRectangle(dpy, win, gc, screen_width - 100, 10, 40, 20);
    XFillRectangle(dpy, win, gc, screen_width - 50, 10, 40, 20);

    XSetForeground(dpy, gc, 0x000000);
    XDrawString(dpy, win, gc, 20, 25, "Launch Kitty", 12);
    XDrawString(dpy, win, gc, screen_width - 90, 25, "Snip", 4);
    XDrawString(dpy, win, gc, screen_width - 40, 25, "Quit", 4);
}

void render_windows(Display *dpy, Window win, GC gc) {
    WindowNode *current = window_list;
    while (current != NULL) {
        XSetForeground(dpy, gc, BlackPixel(dpy, DefaultScreen(dpy)));
        XDrawRectangle(dpy, current->id, gc, 0, 0, current->width, current->height);

        // Draw close button
        XSetForeground(dpy, gc, WhitePixel(dpy, DefaultScreen(dpy)));
        XFillRectangle(dpy, current->id, gc, current->width - 20, 0, 20, 20);
        XSetForeground(dpy, gc, BlackPixel(dpy, DefaultScreen(dpy)));
        XDrawString(dpy, current->id, gc, current->width - 15, 15, "X", 1);

        // Draw window title
        XDrawString(dpy, current->id, gc, 5, 15, current->title, strlen(current->title));

        current = current->next;
    }
}
