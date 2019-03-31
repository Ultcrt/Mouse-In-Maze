
// Created on 2018.12.18
// By Bruce Zhang

#ifndef ROUTE_H
#define ROUTE_H

NODE* RandomMazeSolutions();
int MazeReInitializer();
NODE* MazeSolve(NODE *node);
void SolutionImprint(char identifier, NODE* end);

#endif // !ROUTE_H