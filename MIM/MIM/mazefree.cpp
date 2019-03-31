
// Created on 2018.12.18
// By Bruce Zhang

#include "maze.h"
#include <stdlib.h>

void MazeFree(NODE* initialnode)
{
	free(initialnode);
	initialnode = NULL;
}