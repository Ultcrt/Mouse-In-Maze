
// Created on 2018.12.18
// By Bruce Zhang

#include "maze.h"
#include <stdio.h>

extern int WIDTH;
extern int HEIGHT;
extern NODE* InitialNode;

void MazePrint()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			// Blank text and background -> WAY
			if ((InitialNode + j + i * WIDTH)->MapType == WAY)
				printf("%c", (InitialNode + j + i * WIDTH)->MapType);
			// White text and background ->WALL
			else if ((InitialNode + j + i * WIDTH)->MapType == WALL)
				printf("\033[47;37;5m%c\033[0m",
				(InitialNode + j + i * WIDTH)->MapType);
			// Red text and backgroung -> route
			else
				printf("\033[41;31;5m%c\033[0m", 
				(InitialNode + j + i * WIDTH)->MapType);
		}
		printf("\n");
	}
}