![plane](/extra/images/plane.svg)

# PlaneWM

PlaneWM is a window manager for X that gives you an infinite canvas to spread your windows on.

## Installation

### Dependencies

- [picom](https://github.com/yshui/picom)
- scrot
- libx11

Debian-based systems: libx11-dev picom scrot

Arch-based systems: libx11 picom scrot

### Build

```sh
sudo ./install.sh
paperwm
```

## Configuration

You can keep the configuration file in `~/.config/plane/config` which will be loaded by default. Here is an example of a configuration file:

```
EXEC    some-random-command-you-want-to-run-on-startup --with-arguments
EXEC    some-other-command

KEYBIND mod+enter   xterm
KEYBIND mod+shift+q kill-window

BAR     background-color #000000
BAR     foreground-color #ffffff

GAP     10
```
