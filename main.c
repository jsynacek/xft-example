#include <X11/Xft/Xft.h>

static void die(const char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(1);
}

int main()
{
    Display *dpy;
    int scr;
    Visual *visual;
    Colormap cmap;
    Window win;
    XftFont *font;
    const char *fontname = "DejaVu Sans Mono:size=11:antialias=true";
    XftDraw *draw;
    XftColor color;

    /* Initialization. */
    dpy = XOpenDisplay(NULL);
    if (!dpy)
        die("cannot open X11 display\n");
    scr = DefaultScreen(dpy);
    visual = DefaultVisual(dpy, scr);
    cmap = DefaultColormap(dpy, scr);

    /* Window. */
    win = XCreateSimpleWindow(dpy, RootWindow(dpy, scr), 100, 100, 200, 100, 1, BlackPixel(dpy, scr), WhitePixel(dpy, scr));
    XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    XMapWindow(dpy, win);

    /* Xft. */
    font = XftFontOpenName(dpy, scr, fontname);
    if (!font)
        die("cannot load font\n");
    if (!XftColorAllocName(dpy, visual, cmap, "#0000ee", &color))
        die("cannot allocate xft color\n");
    draw = XftDrawCreate(dpy, win, visual, cmap);

    while(1) {
        XEvent ev;

        XNextEvent(dpy, &ev);
        if (ev.type == Expose)
            XftDrawStringUtf8(draw, &color, font, 50, 50, (const FcChar8 *)"Hello Xft!", 10);
        else if (ev.type == KeyPress)
            break;
    }

    /* Cleanup. Not necessary, only for the sake of completeness. */
    XftColorFree(dpy, visual, cmap, &color);
    XftDrawDestroy(draw);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
}
