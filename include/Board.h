#pragma once

//-------------------------------------------------------------
// includes
//-------------------------------------------------------------

#include "io.h"
#include <vector>
class string;
class Player;
class Deamons;
class Doors;
class Location;
class Play;
class Keys;
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

class Board {
public:

	//set

	void set(Play& play);

	void reset();

	void changhLtr(const Location& location, char ltr);

	//print

	void printBoard(const Doors& doors, const Keys& keys)const;

	void printMove(const Location& prev, const Location& current)const;

	//get

	bool noCookies()const;

	Location search(Location location, char ltr)const;

	char getLtr(const Location& locatuon)const;

	int getRows()const;

	int getCols()const;

private:

	void readNums(Play& play);

	void readBoard(Play& play);

	std::ifstream m_txtBoard;// olds Board.txt
	int m_rowSize;//the size of the board (input from user)
	int m_colSize;
	std::vector <std::string> m_board;
};