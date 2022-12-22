#pragma once

class Location
{
    public:

        Location(int row, int col);

        Location();

        void setInLimits(int rowSize, int colSize);

        //opertaors

        bool operator ==(const Location& other)const;

        Location  operator + (const Location loc)const;

    int m_row;

    int m_col;
};
