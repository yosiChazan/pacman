#pragma once

//-------------------------------------------------------------
// includes
//-------------------------------------------------------------

#include "Location.h"
#include "io.h"

class Board;
class Deamons;
class Play;

class Player
{
public:
	Player();

	//set

	void set(Board& board);

	void reset();

	void setScore(char tool);

	void setScore (int score);

	void setSuper();

	void reduceSuper();

	void changeLoc(const Location& location);

	void changeBoard(const Location& location, Board& board);

	Location move(Play& play);

	void chackLife(Play& play, Deamons& deamons);
	
	//print

	void printLoc()const;

	//get

	bool isSuper()const;

	Location getLocation()const;

	int getLife()const;

	int getScore()const;

	int getSuper()const;

private:

	char plrChar() const;

	Location getUserMove()const;

	Location handleSpecialKey()const;

	Location m_location;
	Location m_firstLoc;
	int m_super = 0;
	int m_life = 3;
	int m_score = 0;
	
};
