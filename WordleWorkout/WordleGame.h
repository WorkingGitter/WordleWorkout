/*!
*	@file
*	@date 2022-01-26
*	@author Richard Chin
*/
#pragma once

// case conversion
#include <cctype>
#include <string>
#include <exception>

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
	WORDLECHAR(char ch, WORDLECHARSTATE wcs) 
		: state(wcs) {

		// Convert all input to uppercase
		c = std::toupper(ch);
	}

	char c;
	WORDLECHARSTATE state;
};

/*!	@brief game engine
*/
class WordleGame
{
public:

	// TODO: Initialise with the word dictionary manager
	WordleGame();

	/*!	@brief returns true, if the board is solved.
	*	@return true, if the current state of the board is
	*			in a solved state.
	*/
	bool is_solved() {
		return false;
	}

	/*!	@brief Indicates if the game is still in play
	*/
	bool is_finished() {
		return false;
	}

	/*!	@brief resets the game state with a new word
	*/
	void start_new_game() {
		throw std::exception("NOT IMPLEMENTED");
	}

	/*!	@brief sets the next word guess
	*	@return true, if word is valid and accepted (but may not be correct).
	*			false, if the word is invalid for whatever reason.
	*/
	bool submit_next_guess(std::string aWord) {
		throw std::exception("NOT IMPLEMENTED");
	}

protected:
};

