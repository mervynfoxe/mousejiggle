// Written by Alex Schaeffer - https://github.com/AMVPh34r
// Based off code by Pioz - https://github.com/pioz
// Compile with: gcc -o mousejiggle.x86_64 mousejiggle.c -lX11

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <X11/Xlib.h>

// Define a boolean datatype, mainly for readability
typedef enum {false, true} bool;

static int delta = 10; // Number of pixels to move the cursor
static int delay = 60; // Seconds between movements
static bool running = true;

static Display *display;

// Handle keyboard interrupt
void int_handler(int dummy) {
	running = false;
}

// Simulate mouse click
void click(int button) {
	// Create and setting up the event
	XEvent event;
	memset(&event, 0, sizeof(event));
	event.xbutton.button = button;
	event.xbutton.same_screen = True;
	event.xbutton.subwindow = DefaultRootWindow(display);
	while(event.xbutton.subwindow) {
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
	XWarpPointer(display, None, None, 0,0,0,0, x, y);
	XFlush(display);
	usleep(1);
}

// Move mouse pointer (absolute)
void move_to(int x, int y) {
	int cur_x, cur_y;
	coords(&cur_x, &cur_y);
	XWarpPointer(display, None, None, 0,0,0,0, -cur_x, -cur_y);
	XWarpPointer(display, None, None, 0,0,0,0, x, y);
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

int run() {
	int movements = 0;
	//int cur_x;
	//int cur_y;

	while(running) {
		// TODO check if mouse was moved manually between movements,
		// only move here if it wasn't.
		//coords(&cur_x, &cur_y);
		sleep(delay);
		move(delta, delta);
		movements++;
		delta = -delta;
	}

	return movements;
}


int main(int argc, char *argv[]) { 
	// Set handler for interrupts
	signal(SIGINT, int_handler);

	// Open X display
	display = XOpenDisplay(NULL);
	if (display == NULL) {
		fprintf(stderr, "Can't open display!\n");
		return -1;
	}

	// Run main loop, print movement count when done
	int movements = run();
	printf("\n%d movements made.\n", movements);

	// Close X display and exit
	XCloseDisplay(display);
	return 0;
}
