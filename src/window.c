// window.c
#include "window.h"
#include <X11/Xutil.h>
#include <stdlib.h>
#include <string.h>

WindowNode *window_list = NULL;

void add_window(Display *dpy, Window id) {
    WindowNode *new_node = malloc(sizeof(WindowNode));
    new_node->id = id;
    
    XWindowAttributes attrs;
    XGetWindowAttributes(dpy, id, &attrs);
    new_node->x = attrs.x;
    new_node->y = attrs.y;
    new_node->width = attrs.width;
    new_node->height = attrs.height;
    
    char *window_name;
    if (XFetchName(dpy, id, &window_name) != 0) {
        new_node->title = strdup(window_name);
        XFree(window_name);
    } else {
        new_node->title = strdup("Untitled");
    }
    
    new_node->next = window_list;
    window_list = new_node;
    
    // Add 10px border
    XSetWindowBorderWidth(dpy, id, 10);
    XSetWindowBorder(dpy, id, BlackPixel(dpy, DefaultScreen(dpy)));
    
    // Add close button (we'll implement this later)
    // For now, just reparent the window
    Window parent = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy),
                                        attrs.x, attrs.y, attrs.width + 20, attrs.height + 30,
                                        1, BlackPixel(dpy, DefaultScreen(dpy)), WhitePixel(dpy, DefaultScreen(dpy)));
    XReparentWindow(dpy, id, parent, 10, 20);
    XMapWindow(dpy, parent);
}

void remove_window(Display *dpy, Window id) {
    WindowNode *current = window_list;
    WindowNode *prev = NULL;
    
    while (current != NULL) {
        if (current->id == id) {
            if (prev == NULL) {
                window_list = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->title);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void focus_window(Display *dpy, Window id) {
    XRaiseWindow(dpy, id);
    XSetInputFocus(dpy, id, RevertToPointerRoot, CurrentTime);
}

void raise_window(Display *dpy, Window id) {
    XRaiseWindow(dpy, id);
}

void update_window_list(Display *dpy) {
    Window root, parent, *children;
    unsigned int nchildren;
    
    XQueryTree(dpy, DefaultRootWindow(dpy), &root, &parent, &children, &nchildren);
    
    for (unsigned int i = 0; i < nchildren; i++) {
        add_window(dpy, children[i]);
    }
    
    if (children) {
        XFree(children);
    }
}

void handle_window_events(Display *dpy, XEvent *ev) {
    switch (ev->type) {
        case MapRequest:
            add_window(dpy, ev->xmaprequest.window);
            XMapWindow(dpy, ev->xmaprequest.window);
            break;
        case UnmapNotify:
            remove_window(dpy, ev->xunmap.window);
            break;
        case ConfigureRequest:
            {
                XConfigureRequestEvent *conf_req = &ev->xconfigurerequest;
                XWindowChanges changes;
                changes.x = conf_req->x;
                changes.y = conf_req->y;
                changes.width = conf_req->width;
                changes.height = conf_req->height;
                changes.border_width = conf_req->border_width;
                changes.sibling = conf_req->above;
                changes.stack_mode = conf_req->detail;
                XConfigureWindow(dpy, conf_req->window, conf_req->value_mask, &changes);
            }
            break;
        case ButtonPress:
            focus_window(dpy, ev->xbutton.window);
            break;
    }
}
