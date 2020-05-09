/*
 * board.cpp
 *
 *  Created on: May 6, 2020
 *      Author: zvshr
 */

#include "Board.h"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <iostream>


#ifdef _WIN32
//for a windows system
  #include <windows.h>

void gotoxy(int x, int y) {
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//position cursor at start of window
	destCoord.X = x;
	destCoord.Y = y;
	SetConsoleCursorPosition(hStdout, destCoord);
	system("CLS");
//	system("clear");
	//std::cout<<"goto"<<std::endl;
//	std::cout<<GetConsoleWindow()<<std::endl;

}

void setColor(int foreground)
{

	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// color your text in Windows console mode
	/*
	The different color codes are

	0   BLACK
	1   BLUE
	2   GREEN
	3   CYAN
	4   RED
	5   MAGENTA
	6   BROWN
	7   LIGHTGRAY
	8   DARKGRAY
	9   LIGHTBLUE
	10  LIGHTGREEN
	11  LIGHTCYAN
	12  LIGHTRED
	13  LIGHTMAGENTA
	14  YELLOW
	15  WHITE
	*/
	// colors are 0=black 1=blue 2=green and so on to 15=white
	// colorattribute = foreground + background * 16
	// to get red text on yellow use 4 + 14*16 = 228
	// light red on yellow would be 12 + 14*16 = 236

	FlushConsoleInputBuffer(hConsole);

	SetConsoleTextAttribute(hConsole, foreground);
}

#else
void gotoxy(int x, int y){}
void setColor(){}
#endif




Board::Board() : X(100), Y(100)
{
	current.resize(Y);
	future.resize(Y);
	for(int i=0; i< Y; i++)
	{
		current[i].resize(X);
		future[i].resize(X);
	}



}

Board::Board(int y, int x) : X(x), Y(y)
{
	current.resize(y);
	future.resize(y);
	for(int i=0; i< y; i++)
	{
		current[i].resize(X);
		future[i].resize(X);
	}

	this->generateLivingCells();
}

void Board::runGame(int generations)
{
	this->generateLivingCells();
	while(generationCount < generations)
	{
		gotoxy(0,0);

		this->printBoard();

		this->advanceGeneration();

	}
	setColor(15);//reset color

}

void Board::generateLivingCells()
{

	srand(time(nullptr));
	for(int i = 0; i < Y; i++)
	{
		for(int j =0; j < X; j++)
		{
			bool random =rand()%2;
			current[i][j].setIsAlive(random);
		}

	}



}


void Board::advanceGeneration()
{

	for(int i =0; i < Y; i++)
	{
		for(int j = 0; j < X; j++)
		{
			//how many neighboring cells are alive
			int neighborLife = 0;
			//check up
			if(i>0)
			{
				neighborLife += current[i-1][j].getIsAlive();
				//check left up
				if(j>0)
				{
					neighborLife += current[i-1][j-1].getIsAlive();
				}
				//check up right
				if(j<X-1)
				{
					neighborLife += current[i-1][j+1].getIsAlive();
				}

			}
			//check left
			if(j>0)
			{
				neighborLife += current[i][j-1].getIsAlive();
			}

			//check down
			if(i<Y-1)
			{
				neighborLife += current[i+1][j].getIsAlive();
				//check down left
				if(j>0)
				{
					neighborLife += current[i+1][j-1].getIsAlive();
				}
				//check down right
				if(j<X-1)
				{
					neighborLife += current[i+1][j+1].getIsAlive();
				}
			}

			//check right
			if(j<X-1)
			{
				neighborLife += current[i][j+1].getIsAlive();
			}


			//apply rules

			//Any live cell with fewer than two live neighbours dies, as if by underpopulation.
			if(current[i][j].getIsAlive() && neighborLife <2)
			{
				future[i][j].setIsAlive(false);
			}
			//Any live cell with two or three live neighbours lives on to the next generation.
			if(current[i][j].getIsAlive() && (neighborLife==2 || neighborLife==3))
			{
				future[i][j].setIsAlive(true);
			}

			//Any live cell with more than three live neighbours dies, as if by overpopulation.
			if(current[i][j].getIsAlive() && neighborLife > 3)
			{
				future[i][j].setIsAlive(false);
			}

			//Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
			if(!current[i][j].getIsAlive() && neighborLife ==3)
			{
				future[i][j].setIsAlive(true);
			}
		}

	}

	//swap boards
	current.clear(); // clear current
	current = future; // move current board to new generation

	generationCount++;

}

int** Board::currentGeneration()
{
	int height = current.size();
	int width = current[1].size();
	int** arr=0;
	arr = new int*[height];
//	std::cout<<"Board is:"<<" Width:"<<X<<" Height:"<<Y<<std::endl;




	for(int i =0; i<height; i++)
	{
		std::cout<<"line "<<i<<std::endl;
		arr[i] = new int[width];
		for(int j=0; j<width; j++)
		{
			bool x = current[i][j].getIsAlive();
			arr[i][j]= x;
			std::cout<<"["<<arr[i][j]<<"]";
		}
		std::cout<<std::endl;
	}
	std::cout<<"End"<<std::endl;
	return arr;
}

void Board::printBoard()
{
	int height = current.size();
	int width = current[1].size();
	for(int i = 0; i< height; i++)
	{
		for(int j =0; j < width; j++)
		{
			int x = current[i][j].getIsAlive();
			if(x==0)
			{
				setColor(4);
			} else
			{
				setColor(2);
			}
			std::cout<<x;
		}
		std::cout<<std::endl;
	}

}
