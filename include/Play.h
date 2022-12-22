#pragma once

//-------------------------------------------------------------
// includes
//-------------------------------------------------------------

#include "Board.h"
#include "Player.h"
#include "Deamons.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "Keys.h"
#include "Doors.h"

//-------------------------------------------------------------
// enum
//-------------------------------------------------------------

enum charactor{Plr = 1, Dmn = 2};


class Play {

public:	
	
	Play();

	void run();

	//print

	void firstPrint()const;

	//get

	std::string getLineOfTxt();

	bool isValid(Location location, charactor objct)const;

	Location getPlrLoc()const;

	int getRows()const;

	int getCols()const;

	int getLevel()const;

private:

	void setGame();

	void reset();

	void exePlrMove(const Location& location);

	void exeDmnMove(const Location location, int index);

	void levelUp();
	
	void gameOver()const;

	void printDetals()const;

	void printMove(const Location& prev, const Location& current)const;

	void getBoardTxt();


	std::ifstream m_boardTxt;
	int m_level;
	Player m_player;
	Deamons m_deamons;
	Board m_board;
	Doors m_doors;
	Keys m_keys;
};