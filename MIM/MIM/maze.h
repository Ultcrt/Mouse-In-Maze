
// Created on 2018.12.18
// By Bruce Zhang

#ifndef MAZE_H
#define MAZE_H

// MapType
#define WALL '*'
#define WAY ' '
#define START 'S'
#define END 'E'

typedef struct
{
	int row, col;
	char MapType; // ' ' for way, '*' for wall
	 /* One specific structure pointer is not 
	 allowed to be involved in that structure itself in VS2017 */
	void* LastNode;
	char Direction;
}NODE;

NODE* RandomMazeGenerate(int width, int height);
void MazeFree(NODE* initialnode);
void MazePrint();
int MazeToTXT(char SolutionIdentifier, const char* title);
int GetMazeInput(int width, int height);

#endif // !MAZE_H

