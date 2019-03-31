
// Created on 2018.12.26
// By Bruce Zhang

#include "maze.h"
#include "route.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int WIDTH;
extern int HEIGHT;
extern NODE* InitialNode;

// For dynamic display use
unsigned int seeds;
unsigned long long int MoveCounter[26] = { 0 };
unsigned long long int MoveTemp = 0;

// Make direction and Lastnode empty
int MazeReInitializer();
NODE* MazeSolve(NODE *node);
void SolutionImprint(char identifier, NODE* end);

// Main solution function: Deep First
NODE* RandomMazeSolutions()
{
	NODE *start = NULL,*SolutionTemp=NULL;
	NODE *SolutionCurrent = NULL;
	unsigned short int solutions= 0;

	seeds = (unsigned int)time(NULL);

	// Set the first seed to rand
	srand(seeds);

	if (MazeReInitializer() == 1)
		return NULL;
	else
	{
		// Set the start node as (1,1) and set the very first current node as start node
		start = InitialNode + 1 + WIDTH;
		start->LastNode = start;
		SolutionCurrent = start;

		// Generate the route
		while ((SolutionCurrent = MazeSolve(SolutionCurrent)) != start)
		{
			// Records every move
			MoveTemp++;

			if (SolutionCurrent == NULL)
				return NULL;
			else if (SolutionCurrent->MapType == END)
			{
				printf("\nSolution %c:\n", 'A' + solutions);
				// Change MapType to route type
				SolutionImprint('a' + solutions, SolutionCurrent);
				// Print solution
				MazePrint();
				// Save solution
				MazeToTXT('a' + solutions,"Solution ");
				// Go back after reach the end
				SolutionTemp = (NODE*)SolutionCurrent->LastNode;
				SolutionCurrent->LastNode = NULL;
				SolutionCurrent = SolutionTemp;
				// Save steps from begin to this solution
				MoveCounter[solutions++] = MoveTemp;
			}
		}

		// In case there is no solution
		if (solutions == 0)
		{
			fprintf(stderr, "No possible solution.\n");
			return NULL;
		}
	}
	return InitialNode;
}

NODE* MazeSolve(NODE *node)
{
	char direction = 0;
	int rowTemp = 0, colTemp = 0;
	NODE *dest = NULL,*LastTemp=NULL;

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
				if (node->row - 1 >= 0)
				{
					rowTemp = node->row - 1;
					colTemp = node->col;
				}
				else
					continue;
				break;
				// Case 0010, DOWN
			case 2:
				if (node->row + 1 < HEIGHT)
				{
					rowTemp = node->row + 1;
					colTemp = node->col;
				}
				else
					continue;
				break;
				// Case 0100, LEFT
			case 4:
				if (node->col - 1 >= 0)
				{
					rowTemp = node->row;
					colTemp = node->col - 1;
				}
				else
					continue;
				break;
				// Case 1000, RIGHT
			case 8:
				if (node->col + 1 < WIDTH)
				{
					rowTemp = node->row;
					colTemp = node->col + 1;
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
			if (dest->MapType != WALL)
			{
				// Make srue the dest have not been explored
				if (dest->LastNode != NULL)
					continue;
				else
				{
					//Save the last node
					dest->LastNode = node;
					return dest;
				}
			}
		}
	}
	// All direction has been explored and still couldn't find end, go back and make the node unexplored
	node->Direction = 15;
	node->MapType = WAY; // Clear identifier
	LastTemp = (NODE*)node->LastNode;
	node->LastNode = NULL;
	return LastTemp;
}

int MazeReInitializer()
{
	NODE *node = NULL;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			node = InitialNode + j + i * WIDTH;
			node->Direction = 15; // In BIN is 1111
			node->LastNode = NULL;
		}
	}
	return 0;
}

void SolutionImprint(char identifier, NODE* end)
{
	// Record solution steps
	unsigned short int counter = 0;
	// Skip end
	NODE* ImprintCurrent = (NODE*)end->LastNode;

	// Loop until reached start
	while (ImprintCurrent->MapType != START)
	{
		counter++;
        ImprintCurrent->MapType = identifier;
		ImprintCurrent = (NODE*)ImprintCurrent->LastNode;
	}
	printf("Step:%d\n", counter);
}