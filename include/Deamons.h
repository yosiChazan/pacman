#pragma once

//-------------------------------------------------------------
// includes
//-------------------------------------------------------------

#include "Location.h"
#include <vector>
#include "Player.h"
#include "io.h"
#include <iostream>
#include <Board.h>

enum Dir { Up, Right, Down, Left };

class Board;

class Deamons
{
public:

	//set

	void set(Board& board);

	void reset();

	void goToStart();

	void setDeamon(const Location& location, int index);

	Location move(Play& play, int index);
	
	//print

	void print()const; 

	void printMove(const Location& prev, const Location& current)const;

	//get

	bool isDeamon(const Location& location)const;

	int getSize()const;
	
	Location getLocation(int i)const;


private:
	std::vector < Dir> findDirs(Play& play, int index)const;

	Location getDir(Dir dir)const;
	
	std::vector <Location> m_location;
	std::vector <Location> m_start;
	std::vector <Location> m_prevLoc;
};

