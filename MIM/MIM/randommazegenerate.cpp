
// Created on 2018.12.18
// By Bruce Zhang

#include "maze.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int WIDTH = 0, HEIGHT = 0;
NODE *InitialNode;

int MazeInitializer();
NODE* MazeLineUp(NODE *node);

//Main Generation function
NODE* RandomMazeGenerate(int width, int height)
{
	NODE *start = NULL;
	NODE *current = NULL;

	srand((unsigned int)time(NULL));

	WIDTH = width;
	HEIGHT = height;

	if (MazeInitializer() == 1)
		return NULL;
	else
	{
		// Set the start node as (1,1)and set the very first current node as start node
		start = InitialNode + 1 + width;
		start->LastNode = start;
		current = start;
		// Generate the maze
		while ((current = MazeLineUp(current)) != start)
		{
			if (current == NULL)
				return NULL;
		}
		// Set start and end
		start->MapType = START;
		(InitialNode + (width - 2) + (height - 2)*width)->MapType = END;
	}
	return InitialNode;
}

int MazeInitializer()
{
	NODE *node = NULL;

	InitialNode = (NODE*)calloc(WIDTH*HEIGHT, sizeof(NODE));

	//In case memory assignment failed
	if (InitialNode == NULL)
	{
		fprintf(stderr, "Cannot assign memory for maze.\n");
		return 1;
	}

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			node = InitialNode + j + i * WIDTH;
			node->row = i;
			node->col = j;
			node->Direction = 15; // In BIN is 1111
			node->LastNode = NULL;
			if (i * j % 2)
				node->MapType = WAY;
			else
				node->MapType = WALL;
		}
	}
	return 0;
}

NODE* MazeLineUp(NODE *node)
{
	char direction = 0;
	int rowTemp = 0, colTemp = 0;
	NODE *dest = NULL;

	// In case parameter is NULL
	if (node == NULL)
	{
		fprintf(stderr, "An unexpected error occured.\n");
		return NULL;
	}

	// Make all directions of one node explored
	while (node->Direction)
	{
		// 'random 0' for 0001, 'random 1' for 0010, 'random 2' for 0100, 'random 3' for 1000
		direction = (1 << (rand() % 4));
		// If this diretion has been explored.
		if (~node->Direction&direction)
			continue;
		else
		{
			// '0' for have been explored, '1' for have not
			node->Direction &= ~direction;
			// Move towards new direction
			switch (direction)
			{
				// Case 0001, UP
			case 1:
				if (node->row - 2 >= 0)
				{
					rowTemp = node->row - 2;
					colTemp = node->col;
				}
				else
					continue;
				break;
				// Case 0010, DOWN
			case 2:
				if (node->row + 2 < HEIGHT)
				{
					rowTemp = node->row + 2;
					colTemp = node->col;
				}
				else
					continue;
				break;
				// Case 0100, LEFT
			case 4:
				if (node->col - 2 >= 0)
				{
					rowTemp = node->row;
					colTemp = node->col - 2;
				}
				else
					continue;
				break;
				// Case 1000, RIGHT
			case 8:
				if (node->col + 2 < WIDTH)
				{
					rowTemp = node->row;
					colTemp = node->col + 2;
				}
				else
					continue;
				break;
			default:
				fprintf(stderr, "An unexpected error occured.\n");
				return NULL;
				break;
			}
			// Make the move
			dest = InitialNode + colTemp + rowTemp * WIDTH;
			// Make sure the dest is not a wall
			if (dest->MapType == WAY)
			{
				// Make srue the dest have not been explored
				if (dest->LastNode != NULL)
					continue;
				else
				{
					//Save the last node
					dest->LastNode = node;
					// Remove the wall between two nodes
					(InitialNode + (colTemp + node->col) / 2 + (rowTemp + node->row)*WIDTH / 2)->MapType = WAY;
					return dest;
				}
			}
		}
	}
	// All direction has been explored,go back
	return (NODE *)node->LastNode;
}