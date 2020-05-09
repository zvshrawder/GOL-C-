
#include "Cell.h"


//basic constructor
Cell::Cell()
{
	this->isAlive = false;
}
Cell::Cell(bool isAlive)
{
	this->isAlive = isAlive;
}


bool Cell::getIsAlive()
{
	bool status = this->isAlive;
	return status;
}

void Cell::setIsAlive(bool isAlive)
{

	this->isAlive = isAlive;
}
