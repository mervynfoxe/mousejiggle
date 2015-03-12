#include <X11/Xlib.h>

static Display *display;

// Simulate mouse click
void click(int button) {
	// Create and setting up the event
	XEvent event;
	memset(&event, 0, sizeof(event));
	event.xbutton.button = button;
	event.xbutton.same_screen = True;
	event.xbutton.subwindow = DefaultRootWindow(display);
	while (event.xbutton.subwindow) {
		event.xbutton.window = event.xbutton.subwindow;
		XQueryPointer(display, event.xbutton.window,
			&event.xbutton.root, &event.xbutton.subwindow,
			&event.xbutton.x_root, &event.xbutton.y_root,
			&event.xbutton.x, &event.xbutton.y,
			&event.xbutton.state);
	}
	// Press
	event.type = ButtonPress;
	if (XSendEvent(display, PointerWindow, True, ButtonPressMask, &event) == 0)
		fprintf(stderr, "Error to send the event!\n");
	XFlush(display);
	usleep(1);
	// Release
	event.type = ButtonRelease;
	if (XSendEvent(display, PointerWindow, True, ButtonReleaseMask, &event) == 0)
		fprintf(stderr, "Error to send the event!\n");
	XFlush(display);
	usleep(1);
}

// Get mouse coordinates
void coords(int *x, int *y) {
	XEvent event;
	XQueryPointer(display, DefaultRootWindow(display),
		&event.xbutton.root, &event.xbutton.window,
		&event.xbutton.x_root, &event.xbutton.y_root,
		&event.xbutton.x, &event.xbutton.y,
		&event.xbutton.state);
	*x = event.xbutton.x;
	*y = event.xbutton.y;
}

// Move mouse pointer (relative)
void move(int x, int y) {
	XWarpPointer(display, None, None, 0, 0, 0, 0, x, y);
	XFlush(display);
	usleep(1);
}

// Move mouse pointer (absolute)
void move_to(int x, int y) {
	int cur_x, cur_y;
	coords(&cur_x, &cur_y);
	XWarpPointer(display, None, None, 0, 0, 0, 0, -cur_x, -cur_y);
	XWarpPointer(display, None, None, 0, 0, 0, 0, x, y);
	usleep(1);
}

// Get pixel color at coordinates x,y
void pixel_color(int x, int y, XColor *color) {
	XImage *image;
	image = XGetImage(display, DefaultRootWindow(display), x, y, 1, 1, AllPlanes, XYPixmap);
	color->pixel = XGetPixel(image, 0, 0);
	XFree(image);
	XQueryColor(display, DefaultColormap(display, DefaultScreen(display)), color);
}

// Perform setup operations
int setup() {
	// Open X display
	display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "Can't open display!\n");
		return -1;
	}
	return 0;
}

// Perform cleanup options before exiting
int cleanup() {
	// Close X display
	XCloseDisplay(display);

	return 0;
}
