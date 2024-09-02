/* Main module of the game */
#include <ncurses.h>
#include "engine.h"

/* Main function of the game */
int main() 
{
	/* Initialize screen */
	initscr();
	/* Start using colors */
	start_color();
	/* Start the menu of the game */
	StartMenu();
	/* End the window */
	endwin();

	return 0;
}