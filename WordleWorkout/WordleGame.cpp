#include "WordleGame.h"
#include <cassert>

// Constructor
WordleGame::WordleGame(std::unique_ptr<WordleDic> dictionary)
{
	m_dicptr = std::move(dictionary);
	reset();
}

void WordleGame::reset() {
	m_tries = 0;

	// Initialise board
	// Now we will have a 5 x 6 array board
	// * 5x6 according to our const m_tries_count and m_word_size.
	m_board.clear();
	for (int line = 0; line < m_tries_count; line++) {
		std::vector<WORDLECHAR> w{ m_word_size, {' ', WORDLECHARSTATE::none} };
		m_board.emplace_back(w);
	}
}

bool WordleGame::test_word(int word_index /*= -1*/) {
	int index = m_tries;
	if (word_index > -1) {
		index = word_index;
	}
	assert(word_index < m_tries_count);
	if (word_index > m_tries_count) {
		return false;
	}

	// TODO:

	return false;
}

bool WordleGame::submit_next_guess(std::string aWord) {
	
	if (is_finished())
		return false;

	m_tries++;

	// TODO:
	// set word in the board array

	// Set word state flags

	return true;
}