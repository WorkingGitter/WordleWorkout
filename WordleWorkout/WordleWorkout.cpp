/*!	
*	Worldle Workout
*/

#include <iostream>
#include <string>
#include "ConsoleIO.h"
#include "wordlegame.h"
#include "wordleDisplay.h"


#define WW_VERSION  "0.1 Alpha"

int main()
{
	// create a new dictionary source
	auto dic = std::make_unique<WordleDic>();
	WordleGame game(std::move(dic));

	// UI
	WordleDisplay display;

	// start a new board
	game.start_new_game();

	// game loop
	int c = 0;
	while (!game.is_finished()) {

		// draw layout
		display.Draw(game);

		// input
		std::string guess_string("");
		std::getline(std::cin, guess_string);
		if ((guess_string == "Q") || (guess_string == "q"))
			break;

		// submit user guess
		if (!game.submit_next_guess(guess_string))
			std::cout << '\a';
	}

	display.Draw(game);
	std::cin.get();
}
