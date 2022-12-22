//-------------------------------------------------------------
// includes
//-------------------------------------------------------------

#include "Deamons.h"
#include "Play.h"

//-------------------------------------------------------------
// 01: set
//-------------------------------------------------------------


void Deamons::set(Board& board)
{
	Location location;
	while (true)
	{
		location = board.search(location, '&');
		if (location.m_row >= board.getRows())
			break;
		m_start.push_back(location);
		board.changhLtr(location, ' ');
	}
	goToStart();
}

//-------------------------------------------------------------
// 02: reset
//-------------------------------------------------------------

void Deamons::reset()
{
	m_start.clear();
	m_location.clear();
}

//-------------------------------------------------------------
// 03: go to start (clear and copy from start)
//-------------------------------------------------------------

void Deamons::goToStart()
{
	int index;
	m_location.clear();
	m_prevLoc.clear();
	for (index = 0; index < m_start.size(); ++index)
	{
		m_prevLoc.push_back(m_start[index]);
		m_location.push_back(m_start[index]);
	}
}

//-------------------------------------------------------------
// 04: set demons
//-------------------------------------------------------------

void Deamons::setDeamon(const Location& location, int index)
{
	m_location[index] = location;
}

//-------------------------------------------------------------
// 05: move
//-------------------------------------------------------------

Location Deamons::move(Play& play, int index)
{
	int size = (play.getRows()) * (play.getCols());
	Location move;
	auto dirs = findDirs(play, index);

	if (dirs.empty())
	{
		Location moveToRtrn = m_prevLoc[index];
		m_prevLoc[index] = m_location[index];
		return moveToRtrn;
	}

	if (dirs.size() == 1)
	{
		m_prevLoc[index] = m_location[index];
		return getDir(dirs[0]) + m_location[index];
	}

	bool plrUp = play.getPlrLoc().m_row - m_location[index].m_row < 0;
	bool plrLeft = play.getPlrLoc().m_col - m_location[index].m_col < 0;
	bool plrDown = play.getPlrLoc().m_row - m_location[index].m_row > 0;
	bool plrRight = play.getPlrLoc().m_col - m_location[index].m_col > 0;
	
	for (int i = 0; i < dirs.size(); ++i)
	{
		if (((plrUp && dirs[i] == Down) || (plrDown && dirs[i] == Up)
			|| (plrLeft && dirs[i] == Right) || (plrRight && dirs[i] == Left)) && rand() % (play.getLevel() + 2) == 0)
			dirs.erase(dirs.begin() + i);
	}

	move = getDir(dirs[rand() % dirs.size()]);
	m_prevLoc[index] = m_location[index];
	return move + m_location[index];
}

//-------------------------------------------------------------
// 06: print
//-------------------------------------------------------------

void Deamons::print()const
{
	for (int i = 0; i < m_location.size(); ++i)
	{
		Screen::setLocation(m_location[i]);
		std::cout << '&';
	}
}

//-------------------------------------------------------------
// 07: print move
//-------------------------------------------------------------

void Deamons::printMove(const Location& prev, const Location& current)const
{
	if (isDeamon(prev))
	{
		Screen::setLocation(prev);
		std::cout << '&';
	}
	if (isDeamon(current))
	{
		Screen::setLocation(current);
		std::cout << '&';
	}
}

//-------------------------------------------------------------
// 08: is deamon? (by location)
//-------------------------------------------------------------

bool Deamons::isDeamon(const Location& location)const
{
	for (int i = 0; i < m_location.size(); ++i)
	{
		if (m_location[i] == location)
			return true;
	}
	return false;
}


//-------------------------------------------------------------
// 09: get size (sum of deamons)
//-------------------------------------------------------------

int Deamons::getSize()const
{
	return int(m_location.size());
}

//-------------------------------------------------------------
// 10: get location
//-------------------------------------------------------------

Location Deamons::getLocation(int i)const
{
	return m_location[i];
}


//private


//-------------------------------------------------------------
// 01: find diractions
//-------------------------------------------------------------

std::vector < Dir> Deamons::findDirs(Play& play, int index)const
{
	std::vector < Dir> dirs;
	for (int i = 0; i < 4; ++i)
		if (play.isValid(m_location[index] + getDir(Dir(i)), Dmn) 
			&& !(m_location[index] + getDir(Dir(i)) == m_prevLoc[index]))
			dirs.push_back(Dir(i));
	return dirs;
}

//-------------------------------------------------------------
// 02: get dir
//-------------------------------------------------------------

Location Deamons::getDir(Dir dir)const
{
	switch (dir)
	{
	case Up:
		return Location(-1, 0);
	case Down:
		return Location(1, 0);
	case Left:
		return Location(0, -1);
	case Right:
		return Location(0, 1);
	default:
		return Location(0, 0);

	}
}