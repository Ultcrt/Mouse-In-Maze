
// Created on 2018.12.26
// By Bruce Zhang and Huang Boqi

#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

extern int WIDTH;
extern int HEIGHT;
extern NODE* InitialNode;

int MazeToTXT(char SolutionIdentifier,const char* title)
{
	FILE *fp = NULL;

	// In case cannot open file
	if (fopen_s(&fp, "Maze.txt", "a"))
	{
		printf("Cannot open file.\n");
		return 1;
	}
	else
	{
		fprintf(fp, "\n%s%c:\n", title, toupper(SolutionIdentifier));
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				fprintf(fp,"%c", (InitialNode + j + i * WIDTH)->MapType);
			}
			fprintf(fp,"\n");
		}
	}
	fclose(fp);
	return 0;
}