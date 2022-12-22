#include "Play.h"
#include "Location.h"
#include "Deamons.h"
#include "io.h"
#include <thread>
#include <chrono>

Play::Play()
	:m_level(1)
{}
//-------------------------------------------------------------
// 01: run
//-------------------------------------------------------------

void Play::run()
{
	Location prevMove, currentMove;

	getBoardTxt();

	while (m_level < 4)
	{
		setGame();

		while (!(m_board.noCookies()))
		{
			prevMove = m_player.getLocation();
			currentMove = m_player.move(*this);
			currentMove.setInLimits(m_board.getRows(), m_board.getCols());
			exePlrMove(currentMove);
			printMove(prevMove, m_player.getLocation());

			for (int i = 0; i < m_deamons.getSize(); ++i)
			{
				prevMove = m_deamons.getLocation(i);
				currentMove = m_deamons.move(*this, i);
				currentMove.setInLimits(m_board.getRows(), m_board.getCols());
				exeDmnMove(currentMove, i);
				std::this_thread::sleep_for(std::chrono::milliseconds(25));
				printMove(prevMove, currentMove);
			}
		}
		levelUp();
		reset();
	}

	gameOver();

}

//-------------------------------------------------------------
// 02: first print. print everything on the screen
//-------------------------------------------------------------

void Play::firstPrint()const
{
	system("cls");
	Screen::resetLocation();
	m_board.printBoard(m_doors, m_keys);
	m_deamons.print();
	m_player.printLoc();
	printDetals();
}

//-------------------------------------------------------------
// 03: get line of text. recive 1 line every time
//-------------------------------------------------------------

std::string Play::getLineOfTxt()
{
	std::string line;
	if(std::getline(m_boardTxt, line))
		return line;
	return "";
}

//-------------------------------------------------------------
// 04: is valid. return if the move is legal
//-------------------------------------------------------------

bool Play::isValid(Location location, charactor objct)const
{
	location.setInLimits(m_board.getRows(), m_board.getCols());

	if (m_board.getLtr(location) == '#')
		return false;
	if (m_doors.isDoor(location))
		if ((!m_player.isSuper() && objct == Plr) || objct == Dmn)
			return false;
	return true;
}

//-------------------------------------------------------------
// 05: get player location
//-------------------------------------------------------------

Location Play::getPlrLoc()const
{
	return m_player.getLocation();
}

//-------------------------------------------------------------
// 06: get rows (of board)
//-------------------------------------------------------------

int Play::getRows()const
{
	return m_board.getRows();
}

//-------------------------------------------------------------
// 07: get cols (of board)
//-------------------------------------------------------------

int Play::getCols()const
{
	return m_board.getCols();
}


//-------------------------------------------------------------
// 07: get level
//-------------------------------------------------------------

int Play::getLevel()const
{
	return m_level;
}


//private


//-------------------------------------------------------------
// 01: set game
//-------------------------------------------------------------

void Play::setGame()
{
	m_board.set((*this));
	m_player.set(m_board);
	m_deamons.set(m_board);
	m_doors.set(m_board);
	m_keys.set(m_board);
	firstPrint();
}

//-------------------------------------------------------------
// 02: reset
//-------------------------------------------------------------

void Play::reset()
{
	m_player.reset();
	m_deamons.reset();
	m_board.reset();
	m_doors.reset();
	m_keys.reset();
}

//-------------------------------------------------------------
// 03: execute player move
//-------------------------------------------------------------

void Play::exePlrMove(const Location& location)
{

	char tool = m_board.getLtr(location);

	m_player.setScore(tool);
	m_player.changeLoc(location);
	m_player.changeBoard(location, m_board);
	m_player.reduceSuper();
	if (m_doors.isDoor(location))
		m_doors.dlt(location);

	if (m_keys.isKey(location))
	{
		m_player.setScore(7);

		if (!m_doors.isEmpty())
			m_doors.dlt();
		m_keys.dlt(location);
	}

	if (tool == '$')
		m_player.setSuper();

	m_player.chackLife(*this, m_deamons);
	if (m_player.getLife() == 0)
		gameOver();
}

//-------------------------------------------------------------
// 04: execute damone move
//-------------------------------------------------------------

void Play::exeDmnMove(const Location location, int index)
{
	m_deamons.setDeamon(location, index);
	m_player.chackLife(*this, m_deamons);
	if (m_player.getLife() == 0)
		gameOver();
}

//-------------------------------------------------------------
// 05: game over
//-------------------------------------------------------------

void Play::gameOver()const
{
	system("cls");
	auto gameOverTxt = std::ifstream("GameOver.txt");
	std::string line;

	while (std::getline(gameOverTxt, line))
		std::cout << line << '\n';

	exit(1);
}

//-------------------------------------------------------------
// 06: print deatels
//-------------------------------------------------------------

void Play::printDetals()const
{
	Screen::setLocation(Location(m_board.getRows(), 0));
	std::cout << "level: " << m_level 
		<< " lives: " << m_player.getLife()
		<< " score: " << m_player.getScore() 
		<< " super moves: " << m_player.getSuper() << "         ";
}

//-------------------------------------------------------------
// 07: print move
//-------------------------------------------------------------

void Play::printMove(const Location& prev, const Location& current)const
{
	m_board.printMove(prev, current);
	m_deamons.printMove(prev, current);
	m_player.printLoc();
	printDetals();

}

//-------------------------------------------------------------
// 08:get board text
//-------------------------------------------------------------

void Play::getBoardTxt()
{
	m_boardTxt = std::ifstream("Board.txt");
}

//-------------------------------------------------------------
// 09: level up
//-------------------------------------------------------------

void Play::levelUp()
{
	m_player.setScore(50+m_deamons.getSize() * 2);
	m_level++;
}



