/*!
*	@file
*	@date 2022-01-26
*	@author Richard Chin
*/

#pragma once
#include "WordleGame.h"
#include "ConsoleIO.h"
#include <io.h>
#include <fcntl.h>


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

	virtual wchar_t tl() = 0;
	virtual wchar_t tr() = 0;
	virtual wchar_t bl() = 0;
	virtual wchar_t br() = 0;
	virtual wchar_t side() = 0;
	virtual wchar_t top() = 0;
	virtual wchar_t bottom() = 0;
};

/*!	@brief Draw box with standard ASCII chars
*/
class BoxAscii : public BoxBase
{
public:
	BoxAscii() {};

	virtual wchar_t tl() override { return L' '; }
	virtual wchar_t tr() override { return L' '; }
	virtual wchar_t bl() override { return L' '; }
	virtual wchar_t br() override { return L' '; }
	virtual wchar_t side() override { return L' '; }
	virtual wchar_t top() override { return L' '; }
	virtual wchar_t bottom() override { return L'-'; }
};

/*!	@brief Draw box with standard ASCII chars
*/
class BoxAsciiEx : public BoxBase
{
public:
	BoxAsciiEx() {};

	virtual wchar_t tl() override { return L'┌'; }
	virtual wchar_t tr() override { return L'┐'; }
	virtual wchar_t bl() override { return L'└'; }
	virtual wchar_t br() override { return L'┘'; }
	virtual wchar_t side() override { return L'│'; }
	virtual wchar_t top() override { return L'─'; }
	virtual wchar_t bottom() override { return L'─'; }
};


/*!	@brief manages the board console UI
*/
class WordleDisplay
{
public:
	WordleDisplay() {

		// create box shape object
		// and pre-render some of the boxes
		//m_boxshape = new BoxAscii();
		m_boxshape = new BoxAsciiEx();
		
		std::wostringstream ss;
		for (int i = 0; i < 5; i++) {
			ss << m_boxshape->tl() << m_boxshape->top() << m_boxshape->tr();
		}
		m_boxes_top_str = ss.str();

		ss.str(L"");
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
				std::wcout << L"GAME OVER: COULD NOT SOLVE";
			}
			else {
				std::wcout << L"GAME OVER: SOLVED!";
			}
		}
		else {
			std::wcout << L"Guess: ";
		}
		m_console.SetColourAttributes(m_bg | FOREGROUND_BRIGHTWHITE);
	}

protected:
	BoxBase* m_boxshape;
	std::wstring m_boxes_top_str;
	std::wstring m_boxes_bottom_str;
	CConsoleIO m_console;
	WORD m_bg;	

	void draw_title() {	
		m_console.SetColourAttributes(m_bg | FOREGROUND_BRIGHTWHITE);
		std::wcout << L" [WORDLE WORKOUT]\n";
		std::wcout << L"  Word of the Day\n\n";
	}

	void draw_keyboard(const WordleGame& game) {
		m_console.SetColourAttributes(m_bg | FOREGROUND_BRIGHTWHITE);
		std::wcout << L"┌────────────────────┐\n";
		draw_line(    L" QWERTYUIOP", game);
		draw_line(    L"  ASDFGHJKL", game);
		draw_line(    L"   ZXCVBNM", game);
		m_console.SetColourAttributes(m_bg | FOREGROUND_BRIGHTWHITE);
		std::wcout << L"└────────────────────┘\n";
	}

	void draw_line(std::wstring linestr, const WordleGame& game) {

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
			std::wcout << c << L" ";
		}
		std::wcout << std::endl;
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
			std::wcout << L"  " << m_boxes_top_str << L"\n";

			std::wcout << L"  ";
			for (auto& c : line) {
				std::wcout << m_boxshape->side();
				m_console.PushColourAttributes();
				m_console.SetColourAttributes(funcGetKeyStateColor(c.state));
				std::wcout << c.c;
				m_console.PopColourAttributes();
				std::wcout << m_boxshape->side();
			}
			std::wcout << L"\n";
			std::wcout << L"  " << m_boxes_bottom_str << L"\n";
		}
	}
};