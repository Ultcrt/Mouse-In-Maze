
// Created on 2018.12.26
// By Bruce Zhang

#include "maze.h"
#include "route.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

// Display speed
#define SPEED 150L

extern int WIDTH;
extern int HEIGHT;
extern NODE* InitialNode;
extern unsigned long long int MoveCounter[26];
extern unsigned int seeds;
// Get correspond solution from Maze.txt

NODE* DynamicDisplay(char identifier)
{
	COORD InitialLocation;
	CONSOLE_CURSOR_INFO CursorInfo;
	// Get cursor handle
	HANDLE Cursor = GetStdHandle(STD_OUTPUT_HANDLE);

	char IdentifierLower = tolower(identifier);
	NODE *start = NULL, *SolutionTemp = NULL;
	NODE *SolutionCurrent = NULL;
	unsigned short int solutions = 0;
	unsigned long long int steps = MoveCounter[IdentifierLower - 'a'];
	// To fix print lag
	double timer = SPEED;

	// Set the initial seed in route.cpp to generate the same route
	srand(seeds);

	// Set the cursor initial location
	InitialLocation.X = 0;
	InitialLocation.Y = 0;

	// Make the cursor disappear
	CursorInfo.bVisible = false;
	CursorInfo.dwSize = 1;
	SetConsoleCursorInfo(Cursor, &CursorInfo);

	// Clean the screen
	system("cls");

	// In case there is no solution
	if (steps == 0)
	{
		fprintf(stderr, "Solution %c does not exist.\n", toupper(identifier));
		return NULL;
	}
	else
	{
		if (MazeReInitializer() == 1)
			return NULL;
		else
		{
			// Set the start node as (1,1) and set the very first current node as start node
			start = InitialNode + 1 + WIDTH;
			start->LastNode = start;
			SolutionCurrent = start;

			// Generate the route until steps run out
			for (; steps > 0; steps--)
			{
				// Search for next node
				SolutionCurrent = MazeSolve(SolutionCurrent);
				// Goto initial location
				SetConsoleCursorPosition(Cursor, InitialLocation);
				if (SolutionCurrent == NULL)
					return NULL;
				else
				{
					printf("\nSolution %c:\n", toupper(identifier));
					// Change MapType to route type
					SolutionImprint('M', SolutionCurrent);
					// If reach end
					MazePrint();
					if (SolutionCurrent->MapType == END)
					{
						// If reach another solution then go back
						SolutionTemp = (NODE*)SolutionCurrent->LastNode;
						SolutionCurrent->LastNode = NULL;
						SolutionCurrent = SolutionTemp;
					}
				}

				// Delay
				for (; timer > 0; timer -= 0.00001);
				timer = SPEED;
			}
		}
	}
	return InitialNode;
}