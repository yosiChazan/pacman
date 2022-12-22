#pragma once

//-------------------------------------------------------------
// includes
//-------------------------------------------------------------

#include "Board.h"
#include <vector>
#include <location.h>
#include <iostream>
#include "io.h"

class Doors
{
public:

	//set

	void set(Board& board);

	void reset();

	void dlt(const Location& location);

	void dlt();

	//print

	void print()const;

	//get

	bool isDoor(const Location& location)const;

	int getIndex(const Location& location)const;

	bool isEmpty()const;

private:

	void dlt(int index);

	std::vector <Location> m_doors;
};