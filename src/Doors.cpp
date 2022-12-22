//-------------------------------------------------------------
// includes
//-------------------------------------------------------------

#include "Doors.h"
#include "Location.h"
#include <vector>
#include <random>
#include <ctime>
#include "Board.h"

//-------------------------------------------------------------
// 01: set
//-------------------------------------------------------------

void Doors::set(Board& board)
{
	Location location;
	while (true)
	{
		location = board.search(location, 'D');
		if (location.m_row >= board.getRows())
			break;
		m_doors.push_back(location);
		board.changhLtr(location, ' ');
	}
}

//-------------------------------------------------------------
// 02: reset
//-------------------------------------------------------------

void Doors::reset()
{
	m_doors.clear();
}

//-------------------------------------------------------------
// 03: delete (by location)
//-------------------------------------------------------------

void Doors::dlt(const Location& location)
{
	dlt(getIndex(location));
}

//-------------------------------------------------------------
// 05: delete (by random)
//-------------------------------------------------------------

void Doors::dlt()
{
	srand(time(0));
	dlt(rand() % m_doors.size());
}

//-------------------------------------------------------------
// 06: print
//-------------------------------------------------------------

void Doors::print()const
{
	for (int i = 0; i < m_doors.size(); ++i)
	{
		Screen::setLocation(m_doors[i]);
		std::cout << 'D';
	}
}

//-------------------------------------------------------------
// 07: is door? (by location)
//-------------------------------------------------------------

bool Doors::isDoor(const Location& location)const
{
	return (getIndex(location) < m_doors.size());
}

//-------------------------------------------------------------
// 08: get index of door (by location)
//-------------------------------------------------------------

int Doors::getIndex(const Location& location)const
{
	int i;
	for (i = 0; i < m_doors.size(); ++i)
		if (m_doors[i] == location)
			return i;
	return i;
}

//-------------------------------------------------------------
// 09: is empty
//-------------------------------------------------------------

bool Doors::isEmpty()const
{
	return m_doors.empty();
}


//private


//-------------------------------------------------------------
// 01: delete (by index)
//-------------------------------------------------------------

void Doors::dlt(int index)
{
	Screen::setLocation(m_doors[index]);
	std::cout << ' ';
	m_doors.erase(m_doors.begin()+index);
}