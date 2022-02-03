/*!
*	@file
*	@date 2022-01-26
*	@author Richard Chin
*/

#pragma once
#include "WordleGame.h"
#include "ConsoleIO.h"


/*!	@brief base UI box elements
*
*	Provides a way of drawing our boxes.
*   In this case, we can swap in/out derived objects
*   that will customise the ascii shapes.
*/
class BoxBase
{
public:
	BoxBase() {};

	virtual char tl() = 0;
	virtual char tr() = 0;
	virtual char bl() = 0;
	virtual char br() = 0;
	virtual char side() = 0;
	virtual char top() = 0;
	virtual char bottom() = 0;
};

/*!	@brief Draw box with standard ASCII chars
*/
class BoxAscii : public BoxBase
{
public:
	BoxAscii() {};

	virtual char tl() override { return ' '; }
	virtual char tr() override { return ' '; }
	virtual char bl() override { return ' '; }
	virtual char br() override { return ' '; }
	virtual char side() override { return ' '; }
	virtual char top() override { return ' '; }
	virtual char bottom() override { return '-'; }
};

/*!	@brief Draw box with standard ASCII chars
*/
class BoxAsciiEx : public BoxBase
{
public:
	BoxAsciiEx() {};

	virtual char tl() override { return L'┌'; }
	virtual char tr() override { return L'┐'; }
	virtual char bl() override { return L'└'; }
	virtual char br() override { return L'┘'; }
	virtual char side() override { return L'│'; }
	virtual char top() override { return L'─'; }
	virtual char bottom() override { return L'─'; }
};


/*!	@brief manages the board console UI
*/
class WordleDisplay
{
public:
	WordleDisplay() {

		// create box shape object
		// and pre-render some of the boxes
		m_boxshape = new BoxAscii();
		
		std::ostringstream ss;
		for (int i = 0; i < 5; i++) {
			ss << m_boxshape->tl() << m_boxshape->top() << m_boxshape->tr();
		}
		m_boxes_top_str = ss.str();

		ss.str("");
		ss.clear();
		for (int i = 0; i < 5; i++) {
			ss << m_boxshape->bl() << m_boxshape->bottom() << m_boxshape->br();
		}
		m_boxes_bottom_str = ss.str();
	}

	void Draw(const WordleGame& game) {

		m_bg = BACKGROUND_BLACK;

		m_console.SetColourAttributes(m_bg | FOREGROUND_WHITE);
		
		m_console.ClearScreen();
		draw_title();
		draw_layout_ascii(game); 
		//draw_layout(game);
		draw_keyboard(game);

		m_console.SetColourAttributes(m_bg | FOREGROUND_BRIGHTWHITE);
		
		if (game.is_finished()) {
			m_bg = BACKGROUND_GRAY;

			if (!game.is_solved()) {
				m_console.SetColourAttributes(m_bg | FOREGROUND_RED);
				std::cout << "GAME OVER: COULD NOT SOLVE";
			}
			else {
				std::cout << "GAME OVER: SOLVED!";
			}
		}
		else {
			std::cout << "Guess: ";
		}
		m_console.SetColourAttributes(m_bg | FOREGROUND_BRIGHTWHITE);
	}

protected:
	BoxBase* m_boxshape;
	std::string m_boxes_top_str;
	std::string m_boxes_bottom_str;
	CConsoleIO m_console;
	WORD m_bg;	

	void draw_title() {	
		m_console.SetColourAttributes(m_bg | FOREGROUND_BRIGHTWHITE);
		std::cout << " [WORDLE WORKOUT]\n";
		std::cout << "  Word of the Day\n\n";
	}

	void draw_keyboard(const WordleGame& game) {
		m_console.SetColourAttributes(m_bg | FOREGROUND_BRIGHTWHITE);
		std::cout << "____________________\n";
		draw_line(   "QWERTYUIOP", game);
		draw_line(   " ASDFGHJKL", game);
		draw_line(   "  ZXCVBNM", game);
		m_console.SetColourAttributes(m_bg | FOREGROUND_BRIGHTWHITE);
		std::cout << "--------------------\n";
	}

	void draw_line(std::string linestr, const WordleGame& game) {

		auto funcGetStateColor = [this](WORDLECHARSTATE s) {
			WORD color = m_bg | FOREGROUND_WHITE;
			switch (s) {
			case WORDLECHARSTATE::correct_position:
			case WORDLECHARSTATE::wrong_position:
				color = m_bg | FOREGROUND_LIGHTGREEN;
				break;
			case WORDLECHARSTATE::wrong:
				color = m_bg | FOREGROUND_GRAY;
				break;
			}
			return color;
		};
		
		for (auto c : linestr) {
			m_console.SetColourAttributes(funcGetStateColor(game.get_state_of_character(c)));
			std::cout << c << " ";
		}
		std::cout << std::endl;
	}

	void draw_layout(const WordleGame& game)
	{
		auto funcGetKeyStateColor = [this](WORDLECHARSTATE s) {
			WORD color = m_bg | FOREGROUND_WHITE;
			switch (s) {
			case WORDLECHARSTATE::correct_position:
				color = m_bg | FOREGROUND_LIGHTGREEN;
				break;
			case WORDLECHARSTATE::wrong_position:
				color = m_bg | FOREGROUND_YELLOW;
				break;
			case WORDLECHARSTATE::wrong:
				color = m_bg | FOREGROUND_GRAY;
				break;
			}
			return color;
		};


		auto & board = game.get_board();

		for (auto& line : board) {

			for (auto& c : line) {
				
				m_console.SetColourAttributes(funcGetKeyStateColor(c.state));

				// convert to underscore for easier display to 
				// the console window.
				auto chr = c.c;
				if (chr == ' ') chr = '_';

				std::cout << "  " << chr << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	void draw_layout_ascii(const WordleGame& game)
	{
		auto funcGetKeyStateColor = [this](WORDLECHARSTATE s) {
			WORD color = m_bg | FOREGROUND_WHITE;
			switch (s) {
			case WORDLECHARSTATE::correct_position:
				color = m_bg | FOREGROUND_LIGHTGREEN;
				break;
			case WORDLECHARSTATE::wrong_position:
				color = m_bg | FOREGROUND_YELLOW;
				break;
			case WORDLECHARSTATE::wrong:
				color = m_bg | FOREGROUND_GRAY;
				break;
			}
			return color;
		};

		auto& board = game.get_board();
		for (auto& line : board) {
			//std::cout << "  " << m_boxes_top_str << "\n";

			std::cout << "  ";
			for (auto& c : line) {
				std::cout << m_boxshape->side();
				m_console.PushColourAttributes();
				m_console.SetColourAttributes(funcGetKeyStateColor(c.state));
				std::cout << c.c;
				m_console.PopColourAttributes();
				std::cout << m_boxshape->side();
			}
			std::cout << "\n";
			std::cout << "  " << m_boxes_bottom_str << "\n";
		}
	}
};