
//-------------------------------------------------------------
// includes
//-------------------------------------------------------------

#include "Board.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Player.h"
#include "Deamons.h"
#include "Doors.h"
#include "Keys.h"
#include "Play.h"
#include "Location.h"
#include "io.h"
#include <stdlib.h>

//-------------------------------------------------------------
// const
//-------------------------------------------------------------

const int LEVEL_SCORE = 50;
const int DEAMON_SCORE = 2;

//-------------------------------------------------------------
// 01: set
//-------------------------------------------------------------

void Board::set(Play& play)
{
	readNums(play);
	readBoard(play);
}

//-------------------------------------------------------------
// 02: reset
//-------------------------------------------------------------

void Board::reset()
{
	m_board.clear();
}

//-------------------------------------------------------------
// 03: change letter
//-------------------------------------------------------------

void Board::changhLtr(const Location& location, char ltr)
{
	m_board[location.m_row][location.m_col] = ltr;
}

//-------------------------------------------------------------
// 04: print board
//-------------------------------------------------------------

void Board::printBoard(const Doors& doors, const Keys& keys)const
{
	for (int row = 0; row < m_rowSize; ++row)
	{
		std::cout << m_board[row] << '\n';
	}
	doors.print();
	keys.print();
}

//-------------------------------------------------------------
// 05: print nove
//-------------------------------------------------------------

void Board::printMove(const Location& prev, const Location& current)const
{
	Screen::setLocation(prev);
	std::cout << getLtr(prev);
	Screen::setLocation(current);
	std::cout << getLtr(current);
}

//-------------------------------------------------------------
// 06: is cookies left?
//-------------------------------------------------------------

bool Board::noCookies()const
{
	return (search(Location(0, 0), '*').m_row == m_rowSize);
}

//-------------------------------------------------------------
// 07: search in teh board
//-------------------------------------------------------------

Location Board::search(Location location, char ltr)const
{
	int i = location.m_row, j = location.m_col + 1;

	for (; i < m_rowSize; i++)
	{
		while (j < m_colSize)
		{
			if (m_board[i][j] == ltr) {
				return { i, j };
			}
			j++;
		}
		j = 0;
	}

	return { i, j };
}

//-------------------------------------------------------------
// 08: get letter (by location)
//-------------------------------------------------------------

char Board::getLtr(const Location& location)const
{
	return m_board[location.m_row][location.m_col];
}

//-------------------------------------------------------------
// 09: get rows size
//-------------------------------------------------------------

int Board::getRows()const
{
	return m_rowSize;
}

//-------------------------------------------------------------
// 10: get cols size
//-------------------------------------------------------------

int Board::getCols()const
{
	return m_colSize;
}

//private
 

//-------------------------------------------------------------
// 01: read nums
//-------------------------------------------------------------

void Board::readNums(Play& play)
{
	std::string line = play.getLineOfTxt();
	auto iss = std::istringstream(line);
	iss >> 	m_rowSize >> m_colSize ;
}

//-------------------------------------------------------------
// 01: read board
//-------------------------------------------------------------

void Board::readBoard(Play& play)
{
	std::string line;

	do	{
		line = play.getLineOfTxt();
		//std::cout << line << '\n';
		m_board.push_back(line);
	} while (!line.empty());
}