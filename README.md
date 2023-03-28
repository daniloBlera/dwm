# A fork of DWM with my configs
Version forked: [6.2](https://dl.suckless.org/dwm/dwm-6.2.tar.gz)

Examples of how it looks with different themes [here][dwm-album]. BTW I use
[dwmblocks][bar] for the status bar.

[dwm-album]: https://imgur.com/a/mgMmCY4
[bar]: https://github.com/torrinfail/dwmblocks


## Patches used
*   dwm-[actualfullscreen][actualfullscreen]-20191112-cb3f58a.diff
*   dwm-[alwayscenter][alwayscenter]-20200625-f04cac6.diff
*   dwm-[bottomstack][bottomstack]-6.1.diff
*   dwm-[centeredmaster][centeredmaster]-6.1.diff
*   dwm-[noborder][noborder]floatingfix-6.2.diff
*   dwm-[push][push]\_no\_master-6.2.diff
*   dwm-[rmaster][rmaster]-6.2.diff
*   dwm-[xrdb][xrdb]-6.2.diff

Note that some unwanted functions were commented out to avoid compilation
warnings. These were:
*   quit &mdash; Avoiding closing DWM without confirmation;
*   enternotify &mdash; Preventing the focus to follow the cursor;

You can find these commented functions on `dwm.c` if you want them back.

[actualfullscreen]: https://dwm.suckless.org/patches/actualfullscreen/
[alwayscenter]: https://dwm.suckless.org/patches/alwayscenter/
[bottomstack]: https://dwm.suckless.org/patches/bottomstack/
[centeredmaster]: https://dwm.suckless.org/patches/centeredmaster/
[noborder]: https://dwm.suckless.org/patches/noborder/
[push]: https://dwm.suckless.org/patches/push/
[rmaster]: https://dwm.suckless.org/patches/rmaster/
[xrdb]: https://dwm.suckless.org/patches/xrdb/

# dwm - dynamic window manager
dwm is an extremely fast, small, and dynamic window manager for X.


## Requirements
In order to build dwm you need the Xlib header files.


## Installation
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    make clean install


## Running dwm
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to connect dwm to a specific display, make sure that
the DISPLAY environment variable is set correctly, e.g.:

    DISPLAY=foo.bar:1 exec dwm

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

    while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
    do
        sleep 1
    done &
    exec dwm


## Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
