//-------------------------------------------------------------
// includes
//-------------------------------------------------------------

#include "Location.h"
#include <iostream>

//-------------------------------------------------------------
// 01: constractor
//-------------------------------------------------------------

Location::Location(int row, int col) : m_row(row), m_col(col) {}

//-------------------------------------------------------------
// 02: constractor
//-------------------------------------------------------------

Location::Location() : Location(0,0) {}

//-------------------------------------------------------------
// 01: set in limits
//-------------------------------------------------------------

void Location::setInLimits(int rowSIze, int colSize)
{
    m_row += rowSIze;
    m_col += colSize;
    m_row = m_row % rowSIze;
    m_col = m_col % colSize;
}

//-------------------------------------------------------------
// 02: operator == (same?)
//-------------------------------------------------------------

bool Location::operator ==(const Location& other)const
{
    return (m_row == other.m_row && m_col == other.m_col);
}

//-------------------------------------------------------------
// 03: operator +
//-------------------------------------------------------------

Location Location::operator + (const Location loc)const
{
    return Location(m_row + loc.m_row, m_col + loc.m_col);
}