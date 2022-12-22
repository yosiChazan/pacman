#pragma once

//-------------------------------------------------------------
// includes
//-------------------------------------------------------------

#include <vector>
#include <Location.h>
#include <iostream>
#include "Board.h"

class Keys
{
public:

	//set

	void set(Board& board);
	
	void reset();

	void dlt(const Location& location);

	//print

	void print()const;

	//get

	bool isKey(const Location& location)const;

private:
	
	int getIndex(const Location& location)const;

	void dlt(int index);

	std::vector <Location> m_keys;
};
