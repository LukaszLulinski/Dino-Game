/* The module that contains the main logic of the game */
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "engine.h"

#define DINO_JUMP					 (0)
#define JUMP_TIME					 (40)
#define JUMP_TIME_UP				 (7)
#define JUMP_TIME_DOWN				 (JUMP_TIME - JUMP_TIME_UP)
#define JUMP_POSITION				 (8)
#define DINO_POSITION_X				 (20)
#define CACTUS_ARRAYS_SIZE  		 (20)
#define SEARCH_IN_CACTUS_ARRAY_CONST (5)
#define PRIZE						 (1)
#define NO_PRIZE					 (0)
#define FLAME_POSITION				 (15)

/* Typedef for the user */
typedef struct 
{
	char name[20];
	char age[3];
} User;

/* Variables and constans initialization */
static const int ArrayCactus1[CACTUS_ARRAYS_SIZE] = 
{
	2, 2, 3, 3, 3, 4, 5, 5, 5, 4, 4, 4, 3, 3, 2, 2, 1, 1, 1, 0
};

static const int ArrayCactus2[CACTUS_ARRAYS_SIZE] =
{
	-1, 3, 3, 4, 4, 4, 5, 6, 6, 6, 5, 5, 4, 3, 3, 3, 2, 1, 1, 0
};

static User sUser;
static int diY = 0;
static int diX = DINO_POSITION_X;
static const int *PointerToArrayCactus;
static int CactusNumber;
int HighestScore;

/* Static functions declarations */
static void Engine();
static void CalculatePrize(int Score, int *Prize);
static void EndGame(int Score);
static void ShowDino(int diX, int diY);
static int ComputeDelayTime(int delayTime);
static bool CheckGame(int y, int x, int diY, int diX);
static void CleanFlameAndVariables(int y, int *x, bool *Flame);
static void DrawCactus(void);

/* Start menu */
void StartMenu() 
{
    /* Read the highest score from file */
	FILE *HighScoreFile;
	HighScoreFile = fopen("./HighScore.txt", "r");
	fscanf(HighScoreFile, "%d", &HighestScore);
	fclose(HighScoreFile);

	int MenuX = getmaxx(stdscr) / 2;
	int MenuY = getmaxy(stdscr) / 2;

	/* Show trex inscription */
	ShowTrex(MenuY, MenuX);

    /* Get information from user */
	mvprintw(MenuY + 1, MenuX - 28, "Write inputs and press enter to start game.");
    mvprintw(MenuY + 2, MenuX - 26, "When you got prize, fire it with 'f' key!");
	mvprintw(MenuY + 3, MenuX - 21, "You can jump with space key!");
	mvprintw(MenuY + 3, MenuX - 24, "You can quit the game with 'q' key!");
	mvprintw(MenuY + 5, MenuX - 15, "Name: ");
	getstr(sUser.name);
	mvprintw(MenuY + 6, MenuX - 15, "Age: ");
	getstr(sUser.age);

	/* Turn off cursor */
	curs_set(FALSE);
	/* Disable echoing of input characters */
	noecho();
	/* Start game engine */
	Engine();
}

/* The main engine */
static void Engine() 
{
	/* Initialize variables */
	char name[20];
	diY = getmaxy(stdscr) - 6;
	int y = diY;	
	int MaxX = getmaxx(stdscr);
	int x = MaxX - 20;
	int Score = 0;
	int DelayTime = 100000;
	char UserInput = 'q';
	int Jump = 0xFF;
	void (*ShowCactus[])(int, int) = {Cactus1, Cactus2};
	int Prize = NO_PRIZE;
	bool Flame = FALSE;
	int fY = 0;
	int fX = 0;
	
	/* Clear the window and set functions to non-blocking mode */
	clear();
	nodelay(stdscr, TRUE);

	/* Box */
	box(stdscr, ACS_VLINE, ACS_HLINE);
	/* Ground */
	mvhline(y + 1, 1, '-', MaxX - 3);

	/* Show informations */
	mvprintw(1, getmaxx(stdscr) - 21, "%s %s", sUser.name, sUser.age);
	mvprintw(2, getmaxx(stdscr) - 21, "Highest score: %d", HighestScore);
	mvprintw(4, getmaxx(stdscr) - 21, "Prize: %d", Prize);

	/* Draw which cactus will be shown at first and set cactus array */
	srand(time(NULL));
	DrawCactus();

	/* Start main loop - check if the game is finished */
	while(TRUE == CheckGame(y, x, diY, diX))
	{
		/* Check user input */
		UserInput = getch();

		if((0 == Score) || (0 == (Score % 400)))
		{
			/* Clean the moon */
			CleanMoon(10, (MaxX / 2) - 10);
			/* Show the sun */
			Sun(10, (MaxX / 2) - 10);
		}
		else if(0 == (Score % 200))
		{
			/* Clean the sun */
			CleanSun(10, (MaxX / 2) - 10);
			/* Show the moon */
			Moon(10, (MaxX / 2) - 10);
		}
		else
		{
			/* do nothing */
		}
		
		/* Increase the score */
		Score++;

		/* Show the score and if player has a prize */
		mvprintw(3, getmaxx(stdscr) - 21, "Score: %d", Score);

		/* Check if player deserved a prize */
		CalculatePrize(Score, &Prize);
		
		/* Check if user want to jump */
		if((' ' == UserInput) && (JUMP_TIME <= Jump))
		{
			Jump = DINO_JUMP;
		}

		if(JUMP_TIME > Jump)
		{
			CleanDino(diY, diX);

			if(JUMP_TIME_UP > Jump)
			{
				diY--;
			}
			else if(JUMP_TIME_DOWN > Jump)
			{
				/* do nothing */
			}
			else
			{
				diY++;
			}

			/* Increment state variable value */
			Jump++;
		}

		/* If flame is fired */
		if(TRUE == Flame)
		{
			/* Check if the cactus has been hit */
			if(((x - fX) <= 1) && ((y - 5) < fY))
			{
				/* If so clean the cactus and the flame */
				CleanFlameAndVariables(fY, &fX, &Flame);
				
				CleanCactus(y, x);
				x = MaxX - 20;
				/* Draw new cactus to be shown */
				DrawCactus();
			}
			/* If cactus has not been hit, move the flame further */
			else if((TRUE == Flame) && (fX < (MaxX - 20)))
			{
				fX++;
				ShowFlame(fY, fX);
			}
			/* If flame is on the edge of the screen, clean it */
			else
			{
				CleanFlameAndVariables(fY, &fX, &Flame);
			}
		}

		if((('f' == UserInput) || ('F' == UserInput)) && (PRIZE == Prize))
		{
			/* Set the flame variable and show the flame */
			fY = diY;
			fX = diX + FLAME_POSITION;
			ShowFlame(fY, fX);
			Flame = TRUE;
			Prize = NO_PRIZE;
			mvprintw(4, getmaxx(stdscr) - 21, "Prize: %d", Prize);
		}

		ShowDino(diY, diX);
	
		/* When cactus is on the edge of the screen clean it and draw what cactus will be shown next */
		if(1 == x)
		{
			CleanCactus(y, x);
			x = MaxX - 20;
			DrawCactus();
		}

		/* Show cactus */
		ShowCactus[CactusNumber](y, x);

		/* Move cactus */
		x--;

		/* Quit the game clicking 'q' button on keyboard */
		if(('q' == UserInput) || ('Q' == UserInput))
		{
			break;
		}

		/* Control the pace of the game */
		usleep(ComputeDelayTime(DelayTime));
	}

	/* End game */
	EndGame(Score);
}

/* Which dinosaur should be printed */
static void ShowDino(int diY, int diX) {

	static int counter = 0;

	if(counter == 0) 
	{
		Dino1(diY, diX);
		counter++;
	}
	else 
	{
		Dino2(diY, diX);
		counter--;
	}
}

/* Make game faster */
static int ComputeDelayTime(int DelayTime) 
{
	DelayTime -= 200;

	return DelayTime;
}

/* Check if the game is going to be finished in this iteration */
static bool CheckGame(int y, int x, int diY, int diX) 
{
	/* Calculate in what place dino is */
	int DinoLocation = x - diX;
	/* Add the cosnt to check the array (array keeps the data in what height dino should be) */
	DinoLocation += SEARCH_IN_CACTUS_ARRAY_CONST;

	/* Check if dino is in the range of cactus */
	if((19 >= DinoLocation) && (0 <= DinoLocation))
	{
		/* Check if dino is on appropriate height */
		if(diY > (y - *(PointerToArrayCactus + DinoLocation)))
		{
			return FALSE;
		}
	}

	return TRUE;
}

/* Finishing function */
static void EndGame(int Score) 
{
	nodelay(stdscr, FALSE);
	int maxX = getmaxx(stdscr);
	int maxY = getmaxy(stdscr);
	ShowLoss(maxY / 2, maxX / 2);
	ShowDinoLoss(diY, diX);

	/* Check if the score is the higher than currently the highest */
	if(Score > HighestScore)
	{
		FILE *HighScoreFile;
		HighScoreFile = fopen("./HighScore.txt", "w");
		fprintf(HighScoreFile, "%d", Score);
		fclose(HighScoreFile);
	}

	char UserInput = getch();
    /* Exit or reset game */
	if(('r' == UserInput) || ('R' == UserInput)) 
	{
		Engine();
	}
	else
	{
		return;
	}
}

/* Calculate if player can have an arrow */
static void CalculatePrize(int Score, int *Prize) 
{
	/* If player covers two screens length, will gain a prize */
	if(0 == (Score % (2 * getmaxx(stdscr))))
	{
		*Prize = PRIZE;
		mvprintw(4, getmaxx(stdscr) - 21, "Prize: %d", *Prize);
	}
}

/* Clean the flame and the flame variables */
static void CleanFlameAndVariables(int y, int *x, bool *Flame)
{
	CleanFlame(y, *x);
	*Flame = FALSE;
	*x = 0;
}

/* Draw the cactus number and set cactus array */
static void DrawCactus(void)
{
	CactusNumber = rand() % 2;

	if(0 == CactusNumber)
	{
		PointerToArrayCactus = ArrayCactus1;
	}
	else
	{
		PointerToArrayCactus = ArrayCactus2;
	}
}
