
// Created on 2018.12.18
// By Bruce Zhang

#include "maze.h"
#include <stdio.h>
#include <stdlib.h>

extern int WIDTH;
extern int HEIGHT;
extern NODE* InitialNode;

int GetMazeInput(int width, int height)
{
	NODE *node = NULL;
	
	WIDTH = width;
	HEIGHT = height;

	InitialNode = (NODE*)calloc(WIDTH*HEIGHT, sizeof(NODE));

	//In case memory assignment failed
	if (InitialNode == NULL)
	{
		fprintf(stderr, "Cannot assign memory for maze.");
		return 1;
	}
	else
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				node = InitialNode + j + i * WIDTH;
				node->row = i;
				node->col = j;
				node->Direction = 15; // In BIN is 1111
				node->LastNode = NULL;
				node->MapType = getchar();
			}
			getchar();
			fflush(stdin);
		}
	}
	return 0;
}