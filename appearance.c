/* The code that contains the appearance of elements if the game */
#include <ncurses.h>
#include "appearance.h"

/* Dino appearance */
void Dino1(int y, int x) 
{
	mvprintw(y-4, x, "          o-o  ");
	mvprintw(y-3, x, "        / (___)");
	mvprintw(y-2, x, ",___.--`  / ");
	mvprintw(y-1, x, " '-._, )_/ ");
	mvprintw(y, x,   "      \\/");
}

void Dino2(int y, int x) 
{
	mvprintw(y-4, x, "          o-o  ");
	mvprintw(y-3, x, "        / (___)");
	mvprintw(y-2, x, ",___.--`  / ");
	mvprintw(y-1, x, " '-._, )_/ ");
	mvprintw(y, x,   "      /\\");
}

/* Eyes of the dino when the game is lost */
void ShowDinoLoss(int y, int x)
{
	attron(COLOR_PAIR(4));
	mvprintw(y - 4, x + 10, "x-x");
	attroff(COLOR_PAIR(4));
}

/* Clean the dino */
void CleanDino(int y, int x) 
{
	mvprintw(y-4, x, "               ");
	mvprintw(y-3, x, "               ");
	mvprintw(y-2, x, "               ");
	mvprintw(y-1, x, "               ");
	mvprintw(y, x,   "               "); 
}

/* Cactuses appearance */
void Cactus1(int y, int x) 
{
	attron(COLOR_PAIR(1));
	mvprintw(y-5, x, "    _  ");
	mvprintw(y-4, x, " _ ( )    ");
	mvprintw(y-3, x, "( \\| | _ ");
	mvprintw(y-2, x, " \\   |/ ) ");
	mvprintw(y-1, x, "  |   _/  ");
	mvprintw(y, x,   "  |  | ");
	attroff(COLOR_PAIR(1));
}

void Cactus2(int y, int x) 
{
	attron(COLOR_PAIR(1));
	mvprintw(y-6, x, "    _ ");
	mvprintw(y-5, x, "   ( ) _ ");
	mvprintw(y-4, x, "  _| |/ ) ");
	mvprintw(y-3, x, " ( \\   /  ");
	mvprintw(y-2, x, "  \\   / ");
	mvprintw(y-1, x, "   | | ");
	mvprintw(y, x,   "   | | ");
	attroff(COLOR_PAIR(1));
}

/* Clean a cactus */
void CleanCactus(int y, int x)
{
	mvprintw(y-6, x, "      ");
	mvprintw(y-5, x, "         ");
	mvprintw(y-4, x, "          ");
	mvprintw(y-3, x, "          ");
	mvprintw(y-2, x, "          ");
	mvprintw(y-1, x, "         ");
	mvprintw(y, x,   "        ");
}

/* Sun appearance */
void Sun(int y, int x) 
{
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	attron(COLOR_PAIR(2));
	mvprintw(y-8, x, "      ;   :   ;");
	mvprintw(y-7, x, "   .   \\_,!,_/   ,");
	mvprintw(y-6, x, "    `.,'     `.,'");
	mvprintw(y-5, x, "     /         \\");
	mvprintw(y-4, x, "~ -- :         : -- ~");
	mvprintw(y-3, x, "     \\         /");
	mvprintw(y-2, x, "    ,'`._   _.'`.");
	mvprintw(y-1, x, "   '   / `!` \\   `");
	mvprintw(y, x,   "      ;   :   ;");
	attroff(COLOR_PAIR(2));
}

/* Clean the sun */
void CleanSun(int y, int x) 
{
	mvprintw(y-8, x, "                     ");
	mvprintw(y-7, x, "                     ");
	mvprintw(y-6, x, "                     ");
	mvprintw(y-5, x, "                     ");
	mvprintw(y-4, x, "                     ");
	mvprintw(y-3, x, "                     ");
	mvprintw(y-2, x, "                     ");
	mvprintw(y-1, x, "                     ");
	mvprintw(y, x,   "                     ");
}

/* Moon appearance */
void Moon(int y, int x) 
{
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	attron(COLOR_PAIR(3));
	mvprintw(y-6, x, "   _.._");
	mvprintw(y-5, x, " .' .-'`");
	mvprintw(y-4, x, "/  /");
	mvprintw(y-3, x, "|  |");
	mvprintw(y-2, x, "\\  \\");
	mvprintw(y-1, x, " '._'-._");
	mvprintw(y, x,   "    ```");
	attroff(COLOR_PAIR(3));
}

/* Clean the moon */
void CleanMoon(int y, int x) 
{
	mvprintw(y-6, x, "        ");
	mvprintw(y-5, x, "        ");
	mvprintw(y-4, x, "        ");
	mvprintw(y-3, x, "        ");
	mvprintw(y-2, x, "        ");
	mvprintw(y-1, x, "        ");
	mvprintw(y, x,   "        ");
}

/* Flame appearance - the prize */
void ShowFlame(int y, int x)
{
	init_pair(4, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(4));
	mvprintw(y - 3, x, " *");
	attroff(COLOR_PAIR(4));
}

/* Clean the flame */
void CleanFlame(int y, int x)
{
	mvprintw(y - 3, x + 1, " ");
}

/* Loss inscription when the game is lost */
void ShowLoss(int y, int x) 
{
	init_pair(4, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(4));
	mvprintw(y-6, x-15, "ll");
	mvprintw(y-5, x-15, "ll");
	mvprintw(y-4, x-15, "ll");
	mvprintw(y-3, x-15, "ll   ,oooooo,   ,ssssss,  ,ssssss, ");
	mvprintw(y-2, x-15, "ll  oo     oo  ss        ss        ");
	mvprintw(y-1, x-15, "ll oo       oo 'sssssss, 'sssssss, ");
	mvprintw(y, x-15,   "ll  oo,   ,oo         ss        ss ");
	mvprintw(y+1, x-15, "ll  'oooooo'   'sssssss' 'sssssss' ");
	attroff(COLOR_PAIR(4));
	mvprintw(y+3, x-14, "Press 'r' to play again or any");
	mvprintw(y+4, x-14, "other button to exit from game");
}

/* Trex inscription at the start of the game */
void ShowTrex(int x, int y) 
{
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	mvprintw(x-7, y-25, "  tt");
	mvprintw(x-6, y-25, "  tt");
	mvprintw(x-5, y-25, "ttttttt rr,rrrrrr  ,eeeeee,   xx,    ,xx ");
	mvprintw(x-4, y-25, "  tt    rrr       eee_____ee   xx, ,xx   ");
	mvprintw(x-3, y-25, "  tt    rr        ee            )xxx(    ");
	mvprintw(x-2, y-25, "  ttt   rr        ee,         ,xx   xx,  ");
	mvprintw(x-1, y-25, "   ttt  rr         eeeeeee   ,xx      xx,");
	attroff(COLOR_PAIR(1));
}
