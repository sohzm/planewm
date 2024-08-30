#include "input.h"
#include "mouse.h"
#include "wm.h"
#include "x11.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handle_button_press_event(Display *dpy, XEvent *ev) {

    unsigned int screen_width = DisplayWidth(dpy, 0);

    if (ev->xbutton.x >= 10 && ev->xbutton.x <= 130 && ev->xbutton.y >= 10 && ev->xbutton.y <= 30) {
        launch_window(dpy, NULL);
    } else if (ev->xbutton.x >= screen_width - 100 && ev->xbutton.x <= screen_width - 60 && ev->xbutton.y >= 10 && ev->xbutton.y <= 30) {
        char *command = "scrot ";
        char *home = getenv("HOME");
        char *relative_path = "/Pictures/Screenshots/Cheese_%y_%m_%d-%H.%M.png";

        printf("Home: %s\n, Relative Path: %s\n command: %s\n", home, relative_path, command);

        char *whole_command = (char *)malloc(strlen(command) + strlen(home) + strlen(relative_path) + 1);
        strcpy(whole_command, command);
        strcat(whole_command, home);
        strcat(whole_command, relative_path);

        system(whole_command);
    } else if (ev->xbutton.x >= screen_width - 50 && ev->xbutton.x <= screen_width - 10 && ev->xbutton.y >= 10 && ev->xbutton.y <= 30) {
        XCloseDisplay(dpy);
        exit(0);
    }
}

char *input_text = NULL;

void handle_key_press_event(Display *dpy, XEvent *ev) {
    XKeyEvent *key_event = (XKeyEvent *)ev;
    KeySym keysym;
    char buffer[2] = {0};

    // EXIT
    XLookupString(key_event, buffer, 1, &keysym, NULL);
    if ((key_event->state & ControlMask) && keysym == XK_q) {
        XCloseDisplay(dpy);
        exit(0);
    }

    // handle other key presses, abc-xyz, 123... and backspace
    if (keysym == XK_BackSpace) {
        if (input_text != NULL) {
            input_text[strlen(input_text) - 1] = '\0';
        }
    } else {
        if (input_text == NULL) {
            input_text = (char *)malloc(2);
            input_text[0] = buffer[0];
            input_text[1] = '\0';
        } else {
            input_text = (char *)realloc(input_text, strlen(input_text) + 2);
            strcat(input_text, buffer);
        }
    }
}

void handle_event(Display *dpy, Window win, GC gc, XEvent *ev) {
    switch (ev->type) {
    case MotionNotify:
        // draw_cursor(dpy, win, ev->xmotion.x, ev->xmotion.y);
        break;
    case Expose:
        handle_expose_event(dpy, win, gc);
        break;
    case MapRequest:
        handle_map_request_event(dpy, ev);
        break;
    case ConfigureRequest:
        handle_configure_request_event(dpy, ev);
        break;
    case ButtonPress:
        handle_button_press_event(dpy, ev);
        break;
    case KeyPress:
        handle_key_press_event(dpy, ev);
        break;
    }
}
