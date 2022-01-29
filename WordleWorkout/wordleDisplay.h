/*!
*	@file
*	@date 2022-01-26
*	@author Richard Chin
*/

#pragma once
#include "WordleGame.h"
#include "ConsoleIO.h"

/*!	@brief manages the board console UI
*/
class WordleDisplay
{
public:
	WordleDisplay() {}

	void Draw(const WordleGame& game) {

		m_bg = BACKGROUND_BLACK;
		/*if (game.is_solved())
			m_bg = BACKGROUND_BLUE;*/

		m_console.SetColourAttributes(m_bg | FOREGROUND_WHITE);
		
		m_console.ClearScreen();
		draw_title();
		draw_layout(game);
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
};