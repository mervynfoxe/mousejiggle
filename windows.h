#define WIN32_LEAN_AND_MEAN // Exclude Extra Windows Crap
#define WIN32_EXTRA_LEAN // Exclude More Windows Crap
#include <windows.h>

// Move mouse pointer (relative)
void move(int x, int y) {
	POINT p;
	GetCursorPos(&p);
	p.x += x;
	p.y += y;
	SetCursorPos(p.x, p.y);
	Sleep(1);
}

// Perform setup operations
void setup() {
	// Nothing needed here
}

// Perform cleanup options before exiting
void cleanup() {
	// Nothing needed here
	getchar();
}