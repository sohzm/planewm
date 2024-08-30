#include "x11.h"
#include "wm.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_window_manager_property(Display *dpy, Window win, const char *property, const char *value) {
    Atom wm_atom = XInternAtom(dpy, property, False);
    XChangeProperty(dpy, win, wm_atom, XInternAtom(dpy, "STRING", False), 8, PropModeReplace, (unsigned char *)value, strlen(value));
    XSelectInput(dpy, win, ExposureMask | SubstructureNotifyMask | ButtonPressMask | KeyPressMask | PointerMotionMask);
}

void handle_map_request_event(Display *dpy, XEvent *ev) {
    XMapWindow(dpy, ev->xmaprequest.window);
}

void handle_configure_request_event(Display *dpy, XEvent *ev) {
    XWindowChanges changes;
    changes.x = ev->xconfigurerequest.x;
    changes.y = ev->xconfigurerequest.y;
    changes.width = ev->xconfigurerequest.width;
    changes.height = ev->xconfigurerequest.height;
    changes.border_width = ev->xconfigurerequest.border_width;
    changes.sibling = ev->xconfigurerequest.above;
    changes.stack_mode = ev->xconfigurerequest.detail;
    XConfigureWindow(dpy, ev->xconfigurerequest.window, ev->xconfigurerequest.value_mask, &changes);
}

void handle_expose_event(Display *dpy, Window win, GC gc) {
}
