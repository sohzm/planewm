#include "config.h"
#include "debug.h"
#include "input.h"
#include "mouse.h"
#include "renderer.h"
#include "window.h"
#include "wm.h"
#include "x11.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct screen_info {
    int screen_num;
    unsigned int width;
    unsigned int height;
};

int main() {

    system("picom &");
    struct config config = read_config();
    for (int i = 0; i < config.num_commands; i++) {
        system(config.commands[i]);
    }

    Display *dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        fprintf(stderr, "Unable to open display\n");
        return 1;
    }

    struct screen_info screen_info = {0};
    screen_info.screen_num = DefaultScreen(dpy);
    screen_info.width = DisplayWidth(dpy, screen_info.screen_num);
    screen_info.height = DisplayHeight(dpy, screen_info.screen_num);

    Window win = XCreateSimpleWindow(dpy, RootWindow(dpy, 0), 0, 0, screen_info.width, screen_info.height, 1, BlackPixel(dpy, 0), WhitePixel(dpy, 0));
    set_window_manager_property(dpy, win, "_NET_WM_WINDOW_MANAGER", "window_manager");

    GC gc = XCreateGC(dpy, win, 0, NULL);

    XSetForeground(dpy, gc, BlackPixel(dpy, 0));
    XSync(dpy, False);
    XMapWindow(dpy, win);
    update_window_list(dpy);

    init_mouse_gc(dpy, win);
    init_debug_gc(dpy, win);

    XEvent ev;
    XSync(dpy, False);

    while (!XNextEvent(dpy, &ev)) {
        handle_window_events(dpy, &ev);  // Add this line
        handle_event(dpy, win, gc, &ev);
        render_screen(dpy, win, gc, &ev);
    }

    return 0;
}
