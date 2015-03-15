#define WIN32_LEAN_AND_MEAN // Exclude Extra Windows Crap
#define WIN32_EXTRA_LEAN // Exclude More Windows Crap
#include <windows.h>

// Simulate mouse click
void click(int button) {

}

// Get mouse coords
void coords(int *x, int *y) {

}

// Move mouse pointer (relative)
void move(int x, int y) {
	POINT p;
	GetCursorPos(&p);
	p.x += x;
	p.y += y;
	SetCursorPos(p.x, p.y);
	Sleep(1);
}

// Move mouse pointer (absolute)
void move_to(int x, int y) {

}

// Get pixel color at coordinates x,y
void pixel_color(int x, int y) {

}

// Perform setup operations
int setup() {
	// Nothing needed here
	return 0;
}

// Perform cleanup options before exiting
int cleanup() {
	// Nothing needed here
	printf("Press Enter to continue...");
	getchar();
	return 0;
}
