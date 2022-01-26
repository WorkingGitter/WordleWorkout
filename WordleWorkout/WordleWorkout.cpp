/*!	
*	Worldle Workout
*/

#include <iostream>
#include <string>
#include "ConsoleIO.h"
#include "wordlegame.h"


#define WW_VERSION  "0.1"

int main()
{
	WordleGame game;

	// start a new board
	game.start_new_game();

	// game loop
	while (!game.is_finished()) {

		// draw layout
		std::cout << "Guess: ";

		// input
		std::string guess_string("");
		std::getline(std::cin, guess_string);

		// submit user guess
		bool accepted = game.submit_next_guess(guess_string);

		if (!accepted) {
			std::cerr << "Invalid word guess. Please try again";
		}
	}
}
