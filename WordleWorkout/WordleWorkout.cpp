/*!	
*	Worldle Workout
*/

#include <iostream>
#include <string>
#include "ConsoleIO.h"
#include "wordlegame.h"


#define WW_VERSION  "0.1 Alpha"

int main()
{
	// create a new dictionary source
	auto dic = std::make_unique<WordleDic>();
	WordleGame game(std::move(dic));

	// start a new board
	game.start_new_game();

	// game loop
	int c = 0; 
	while (!game.is_finished()) {

		// draw layout
		std::cout << "Guess " << ++c << " : ";

		// input
		std::string guess_string("");
		std::getline(std::cin, guess_string);

		if ((guess_string == "Q") || (guess_string == "q"))
			break;

		// submit user guess
		bool accepted = game.submit_next_guess(guess_string);

		if (!accepted) {
			std::cerr << "Invalid word guess. Please try again";
		}

	}

	if (game.is_solved())
		std::cout << "Correct!\n";
	else
		std::cout << "Word not found\n";
}
