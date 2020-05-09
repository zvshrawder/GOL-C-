/*
 *
 */

//only include if not already included
//this is a header guard
#pragma once


//some funcs for geting and setting the cells values

class Cell
{
public:
	Cell();//default constructor
	Cell(bool); //will take a value for if the cell is alive

	bool getIsAlive();
	void setIsAlive(bool);
private:
	bool isAlive;

};


