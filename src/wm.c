#include "wm.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

Window kitty_window;

void launch_window(Display *dpy, char *binary) {
    kitty_window = XCreateWindow(dpy, RootWindow(dpy, 0), 600, 600, 300, 300, 1,
                                 CopyFromParent, InputOutput, CopyFromParent, 0, NULL);

    // Set window properties
    XStoreName(dpy, kitty_window, "Kitty");

    // Map the window
    XMapWindow(dpy, kitty_window);

    // Sync the display to ensure the window is created before launching kitty
    XFlush(dpy);

    // launch kitty in the window
    if (fork() == 0) {
        execv("/usr/bin/kitty", (char *[]) {"/usr/bin/kitty", NULL});
    }
}
