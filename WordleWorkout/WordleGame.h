/*!
*	@file
*	@date 2022-01-26
*	@author Richard Chin
*/
#pragma once

// case conversion
#include <cwctype>
#include <string>
#include <exception>
#include <memory>
#include <vector>
#include <map>
#include "wordledictionary.h"

/*!	@brief stores the guess state of a character
*/
enum class WORDLECHARSTATE {
	none,
	wrong,
	correct_position,
	wrong_position
};

/*!	@brief Represents a wordle character
*	
*	All characters will automatically be uppercased.
*/
struct WORDLECHAR {

	/*!	Constructor
	*
	*	We should always try to use this constructor.
	*	@remarks
	*		Maybe a class would be better to encapsulate some of this
	*		process.
	*/
	WORDLECHAR(wchar_t ch, WORDLECHARSTATE wcs) 
		: state(wcs) {

		// Convert all input to uppercase
		c = std::towupper(ch);
	}

	wchar_t c;
	WORDLECHARSTATE state;
};

/*!	@brief game engine
*/
class WordleGame
{
public:

	WordleGame(std::unique_ptr<WordleDic> dictionary);

	/*!	@brief returns true, if the board is solved.
	*	@return true, if the current state of the board is
	*			in a solved state.
	*/
	bool is_solved() const {
		return m_is_solved;
	}

	/*!	@brief Indicates if the game is still in play
	*/
	bool is_finished() const {
		
		// we have exceeded our tries
		if (m_tries >= m_tries_count)
			return true;

		return is_solved();
	}

	/*!	@brief resets the game state with a new word
	*/
	void start_new_game() {
		reset();
	}

	/*!	@brief sets the next word guess
	*	
	*	@param aWord a 6 letter word
	*	@return true, if word is valid and accepted (but may not be correct).
	*			false, if the word is invalid for whatever reason.
	*/
	bool submit_next_guess(std::wstring aWord);

	WORDLECHARSTATE get_state_of_character(const wchar_t c) const {
		auto it = m_charstatemap.find(std::towupper(c));
		if (it == m_charstatemap.end())
			return WORDLECHARSTATE::none;

		return it->second;
	}

	const std::vector< std::vector<WORDLECHAR> >& get_board() const {
		return m_board;
	}

protected:

	static const int m_word_size = 5;
	static const int m_tries_count = 6;

	/*!	@brief Dictionary manager
	*/
	std::unique_ptr<WordleDic> m_dicptr;

	/*!	@brief try attempt counter
	*/
	int m_tries;

	/*!	@brief 
	*/
	bool m_is_solved;

	/*!	@brief array structure that will hold words
	*/
	std::vector< std::vector<WORDLECHAR> > m_board;

	/*!	@brief stores the character state for current game play
	*/
	std::map<wchar_t, WORDLECHARSTATE> m_charstatemap;

protected:

	/*!	@brief resets the internal variables and board state
	*/
	void reset();
};

