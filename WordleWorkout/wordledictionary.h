/*!
*	@file
*	@date 2022-01-26
*	@author Richard Chin
* 
*	Encapsulates the dictionary word source that will be used
*	for our game.
*/

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cassert>

/*!	@brief manages the collection of words used in the game
*/
class WordleDic
{
public:
	WordleDic() {
		loadWordTable();
	}

	/*!	@brief returns our key word of the day
	* 
	*	This algorithm ensures that the same word will be used
	*	for a given date.
	* 
	*	It first gets the number of day since 1970 (using the time()) method.
	*	This ensures we have a consistent number for any given day.
	*	
	*	Then we use this as a seed to our random number generator. Using 
	*	the same seed, will give the same random number sequence.
	* 
	*	Finally, use this random number as an index into our dictionary
	*	vector.
	*/
	std::string get_star_word() {

		// get current time
		// This returns the number of seconds since Jan 1st, 1970.
		__int64 now = time(0);

		// Get number of days and cast down to an 
		// unsigned integer for seeding.
		__int64 dys64 = now / (60 * 60 * 24ull);
		unsigned dys32 = static_cast<unsigned>(dys64);

		// Get a random number. This will always be the same
		// for the given date.
		std::srand(dys32);
		int random_index = std::rand();

		// ensure this is within the dictionary array range
		int dic_index = random_index % static_cast<int>(m_wordlist.size());
		assert((dic_index >= 0) && (dic_index < m_wordlist.size()));

		return m_wordlist[dic_index];
	}

	/*!	@brief Checks if given word is in our dictionary
	*/
	bool is_a_word(std::string w) {
		
		// convert string to upper case
		std::for_each(w.begin(), w.end(), [](char& c) {
				c = ::toupper(c);
			});

		return std::binary_search(m_wordlist.begin(), m_wordlist.end(), w);
	}

protected:

	/*!	@brief contains the **sorted** list of uppercase words
	*/
	std::vector<std::string> m_wordlist;


	/*!	@brief loads the list of words
	* 
	*	This will populate our word lookup table with the
	*	complete set of words available.
	*	
	*/
	void loadWordTable() {
		std::ifstream f(R"(C:\dev\WordleWorkout\WordleWorkout\words\wordlist_5letters.txt)");
		if (f.is_open()) {

			std::string line;
			while (std::getline(f, line)) {
				m_wordlist.push_back(line);
			}
			f.close();

			std::sort(m_wordlist.begin(), m_wordlist.end());
		}
	}
};