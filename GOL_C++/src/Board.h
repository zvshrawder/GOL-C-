/*
 * board.h
 *
 *  Created on: May 6, 2020
 *      Author: zvshr
 */


//these are the other header guard pragma once would also work as long as the compiler excepts it (most do)
#ifndef SRC_BOARD_H_
#define SRC_BOARD_H_

#include "Cell.h"
#include <vector>

class Board
{
public:
	Board();
	Board(int x,int y);
	void computeNextGeneration();
	void runGame(int);
	int** currentGeneration(); //returns a 2Dvector (vector of vectors) of bool values (0 is dead 1 is alive)


private:


	const int X =0;
	const int Y =0;
	int generationCount = 0;
	int howManyGenerations = 0;


	std::vector<std::vector<Cell>> current;
	std::vector<std::vector<Cell>> future;

	//Randomly sets cells on the board as living or not
	void generateLivingCells();

	//advances the current vector by one generation
	void advanceGeneration();

	//
	void printBoard();

};



#endif /* SRC_BOARD_H_ */
