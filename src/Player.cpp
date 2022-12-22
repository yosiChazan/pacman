#include "Player.h"
#include "Deamons.h"
#include "Board.h"
#include <conio.h>
#include <iostream>
#include <Play.h>

const int SpecialKey = 224;


enum SpecialKeys
{
    KB_Up = 72,
    KB_Down = 80,
    KB_Left = 75,
    KB_Right = 77,
};

//--------------------------------------------------------------------
// constractor
//--------------------------------------------------------------------

Player::Player() 
    :m_life(3), m_score(0), m_super(0)
{}

//--------------------------------------------------------------------
// 01: set
//--------------------------------------------------------------------

void Player::set(Board& board)
{
	m_location = m_firstLoc = board.search(Location(0, 0), 'a');
	board.changhLtr(m_location, ' ');

}

//--------------------------------------------------------------------
// 02: reset
//--------------------------------------------------------------------

void Player::reset()
{
    m_super = 0;
}

//--------------------------------------------------------------------
// 03: set score(with char)
//--------------------------------------------------------------------

void Player::setScore(char tool)
{
    switch (tool) {
    case '$':
        m_score += 3;
    case '*':
        m_score += 2;
    }
}


//--------------------------------------------------------------------
// 04: set score (with int)
//--------------------------------------------------------------------

void Player::setScore(int score)
{
    m_score += score;
}

//--------------------------------------------------------------------
// 05: set super
//--------------------------------------------------------------------

void Player::setSuper()
{
    m_super = 20;
}

//--------------------------------------------------------------------
// 06: reduce super
//--------------------------------------------------------------------

void Player::reduceSuper()
{
    if (isSuper())
        m_super--;
}

//--------------------------------------------------------------------
// 07: change location
//--------------------------------------------------------------------

void Player::changeLoc(const Location& location)
{
    m_location = location;
}

//--------------------------------------------------------------------
// 08: change board
//--------------------------------------------------------------------

void Player::changeBoard(const Location& location, Board& board)
{
    board.changhLtr(location, ' ');
    Screen::setLocation(Location(10, 0));
}

//--------------------------------------------------------------------
// 09: move
//--------------------------------------------------------------------

Location Player::move(Play& play)
{
    Location move;

    do {
        move = getUserMove();
        if (move == Location(0, 0))
            break;
    } while (move == Location(2, 2) || !play.isValid((m_location + move), Plr));
    return m_location + move;
}

//--------------------------------------------------------------------
// 10: chack life
//--------------------------------------------------------------------

void Player::chackLife(Play& play, Deamons& deamons)
{
    if (deamons.isDeamon(m_location) && !isSuper())
    {
        m_life--;
        deamons.goToStart();
        m_location = m_firstLoc;
        play.firstPrint();
    }
}

//--------------------------------------------------------------------
// 11: print location
//--------------------------------------------------------------------

void Player::printLoc()const
{
	Screen::setLocation(m_location);
	std::cout << plrChar();
}

//--------------------------------------------------------------------
// 12: is super?
//--------------------------------------------------------------------

bool Player::isSuper()const
{
	return m_super > 0;
}

//--------------------------------------------------------------------
// 13: get location
//--------------------------------------------------------------------

Location Player::getLocation()const
{
	return m_location;
}

//--------------------------------------------------------------------
// 14: get life
//--------------------------------------------------------------------

int Player::getLife()const
{
	return m_life;
}

//--------------------------------------------------------------------
// 15: get score
//--------------------------------------------------------------------

int Player::getScore()const
{
	return m_score;
}

//--------------------------------------------------------------------
// 16: get super
//--------------------------------------------------------------------

int Player::getSuper()const
{
    return m_super;
}


//private


//--------------------------------------------------------------------
// 01: player char
//--------------------------------------------------------------------

char Player::plrChar() const
{
	return (isSuper()) ? '@' : 'a';
}

//--------------------------------------------------------------------
// 02: get user move
//--------------------------------------------------------------------

Location Player::getUserMove()const
{
    auto c = _getch();
    switch (c)
    {
    case 0:
    case SpecialKey:
        return handleSpecialKey();
    case ' ':
        return Location(0, 0);
    default:
        return Location(2, 2);
    }
}

//--------------------------------------------------------------------
// 03: handle special key
//--------------------------------------------------------------------

Location Player::handleSpecialKey()const
{
    auto c = _getch();
    switch (c)    {
    case KB_Up:
        return { -1,0 };
    case KB_Down:
        return { 1,0 };
    case KB_Left:
        return { 0, -1 };
    case KB_Right:
        return { 0,1 };
    default:
        return { 2,2 };
    }
}