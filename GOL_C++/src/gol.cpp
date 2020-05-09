//============================================================================
// Name        : gol.cpp
// Author      : Zachary V Shrawder
// Version     : 1.0
// Copyright   : N/A (Developed in 2020)
// Description : Game of life. Initial dev in Eclipse with target to run on windows.


//
//GOL Rules:
//			Any live cell with fewer than two live neighbours dies, as if by underpopulation.
//			Any live cell with two or three live neighbours lives on to the next generation.
//			Any live cell with more than three live neighbours dies, as if by overpopulation.
//			Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
//============================================================================
//


//since board.h is relative to our main file we use quotes. iostream for instance is not so we can use <> to include ones the compiler has set to it
//If compiler provided library uses .h convention is that it is part of the C standard library
//iostream is a cpp standard one (for our custom written ones I use .h to easily differentiate from others.
//#include "board.h"
#include <iostream>
#include <cstdio>
#include "Board.h"
using namespace std;


#ifdef _WIN32
void pause()
{
	system("pause");
}
#else
void pause()
{}
#endif

void printBoard(int ** arr, int width, int height);
int main()
{
	bool run = true;


	while(run)
	{
		//1. get user input on board size
		int x,y=0;

		cout<<"Hello what dimensions do you want for the game board (Y X)"<<endl;

		scanf("%d %d",&y,&x);





		//2. generate board
		Board * board = new Board(y, x);

		//3. ask how many generations should be generated
		int gen =0;
		cout<<"How many generations do you want?"<<endl;
		scanf("%d",&gen);
		board->runGame(gen);

		//	int** out = board->currentGeneration();
		//printBoard(out,x,y);

		//4. animate stopping at last generation

		printf("Do you want to 'play' again?\nIf so enter Y\n");
		char c;
		scanf(" %c",&c);
		if(c!='y'&&c!='Y')
		{
			run = false;
			cout<<"false"<<endl;
		}
		delete board;
	}

	pause();//stop console from auto closing

return 0;
}


void printBoard(int ** arr, int width, int height)
{
	for(int i = 0; i < width; i++)
	{
		for(int j =0; j <height; j++)
		{
			//cout<<arr[i][j];
		}
		//cout<<endl;
	}

}
