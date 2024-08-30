#!/bin/sh

mkdir -p bin
gcc -o bin/planewm src/planewm.c src/config.c src/x11.c src/wm.c src/mouse.c src/input.c src/renderer.c src/debug.c src/window.c -lX11

cp extra/planewm.desktop /usr/share/xsessions/planewm.desktop
cp bin/planewm /usr/bin/planewm
