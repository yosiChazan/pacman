//-------------------------------------------------------------
// includes
//-------------------------------------------------------------

#include <Keys.h>

//-------------------------------------------------------------
// 01: set
//-------------------------------------------------------------

void Keys::set(Board& board)
{
	Location location;
	while (true)
	{
		location = board.search(location, '%');
		if (location.m_row >= board.getRows())
			break;
		m_keys.push_back(location);
		board.changhLtr(location, ' ');
	}
}

//-------------------------------------------------------------
// 02: reset
//-------------------------------------------------------------

void Keys::reset()
{
	m_keys.clear();
}

//-------------------------------------------------------------
// 03: delete (by location)
//-------------------------------------------------------------

void Keys::dlt(const Location& location)
{
	dlt(getIndex(location));
}

//-------------------------------------------------------------
// 04: print
//-------------------------------------------------------------

void Keys::print()const
{
	for (int i = 0; i < m_keys.size(); ++i)
	{
		Screen::setLocation(m_keys[i]);
		std::cout << '%';
	}
}

//-------------------------------------------------------------
// 05: is key? (by location)
//-------------------------------------------------------------

bool Keys::isKey(const Location& location)const
{
	//std::cout << getIndex(location) << ' ' << m_keys.size();
	return getIndex(location) < m_keys.size();
}


//privte


//-------------------------------------------------------------
// 01: get index (by location)
//-------------------------------------------------------------

int Keys::getIndex(const Location& location)const
{
	int index;
	for (index = 0; index < m_keys.size(); ++index)
		if (m_keys[index] == location)
			return index;
	return index;
}


//-------------------------------------------------------------
// 02: delete (by index)
//-------------------------------------------------------------

void Keys::dlt(int index)
{
	m_keys.erase(m_keys.begin() + index);
}