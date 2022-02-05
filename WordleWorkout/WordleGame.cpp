#include "WordleGame.h"
#include <cassert>
#include <locale>
#include <algorithm>
#include <iostream>

// Constructor
WordleGame::WordleGame(std::unique_ptr<WordleDic> dictionary)
{
	m_dicptr = std::move(dictionary);
	reset();
}

void WordleGame::reset() {
	m_tries = 0;
	m_is_solved = false;

	m_charstatemap.clear();

	// Initialise board
	// Now we will have a 5 x 6 array board
	// * 5x6 according to our const m_tries_count and m_word_size.
	m_board.clear();
	for (int line = 0; line < m_tries_count; line++) {
		std::vector<WORDLECHAR> w{ m_word_size, {L' ', WORDLECHARSTATE::none} };
		m_board.emplace_back(w);
	}
}

bool WordleGame::submit_next_guess(std::wstring aWord) {
	
	if (is_finished())
		return false;

	// The word must not exceed our limit
	if (aWord.length() != m_word_size) {
		return false;
	}

	// Check if this is a valid English word
	if (!m_dicptr->is_a_word(aWord)) {
		return false;
	}

	// Set word in the board array
	for (int c = 0; c < m_word_size; c++) {
		m_board[m_tries][c] = { aWord[c], WORDLECHARSTATE::none };
	}

	// 
	auto golden_word = m_dicptr->get_star_word();
	assert(golden_word.length() == m_word_size);

	// convert string to upper case
	std::for_each(golden_word.begin(), golden_word.end(), [](wchar_t& c) {
		c = ::towupper(c);
		});


	// lamdba function
	// Searches 'basestring' for the character 'ch' at location, 'loc'
	auto fnGetCharState = [](const std::wstring& basestring, const wchar_t ch, const int loc) -> WORDLECHARSTATE {
		
		// test if we have a match
		if (basestring[loc] == ch)
			return WORDLECHARSTATE::correct_position;

		bool found = false;
		for (const auto& c : basestring) {
			if (c == ch) {
				found = true;
				break;
			}
		}

		return found ? WORDLECHARSTATE::wrong_position : WORDLECHARSTATE::wrong;
	};
	
	for (int i = 0; i < m_word_size; i++) {
		m_board[m_tries][i].state = fnGetCharState(golden_word, m_board[m_tries][i].c, i);

		// update global character state
		// For each character, we only need to track:
		// all except the 'none' state.
		if (m_board[m_tries][i].state != WORDLECHARSTATE::none) {
			
			// only update if the state has changed
			auto it = m_charstatemap.find(m_board[m_tries][i].c);
			if (it == m_charstatemap.end()) {
				m_charstatemap[m_board[m_tries][i].c] = m_board[m_tries][i].state;
			}
		}
	}

	// set the solved state
	m_is_solved = true;
	for (int i = 0; i < m_word_size; i++) {
		m_is_solved &= (m_board[m_tries][i].state == WORDLECHARSTATE::correct_position);
	}

	m_tries++;

	return true;
}