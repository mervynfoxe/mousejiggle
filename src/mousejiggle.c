// Written by Alex Schaeffer - https://github.com/AMVPh34r
// Based off code by Pioz - https://github.com/pioz
// Compile with: gcc -o mousejiggle.x86_64 mousejiggle.c -lX11

#include <stdio.h>
#include <string.h>
#include <signal.h>
#ifdef __unix__
# include "linux.h"
#elif defined _WIN32
# include "windows.h"
# define sleep(x) Sleep(1000 * x)
#endif

// Define a boolean datatype, mainly for readability
typedef enum {false, true} bool;

static int delta = 10; // Number of pixels to move the cursor
static int delay = 60; // Seconds between movements
static bool running = true;

// Handle keyboard interrupt
void int_handler(int dummy) {
	running = false;
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
	if (setup() != 0)
		return -1;

	// Run main loop, print movement count when done
	int movements = run();
	printf("\n%d movements made.\n", movements);

	cleanup();
	return 0;
}
