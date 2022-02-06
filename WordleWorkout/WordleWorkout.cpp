/*!	
*	Worldle Workout
*/

#include <iostream>
#include <string>
#include "ConsoleIO.h"
#include "wordlegame.h"
#include "wordleDisplay.h"


#define WW_VERSION  "0.3 Alpha"

/*
*  DISPLAY
*  =======
* 
*  For this application, we are using some of the box characters.
*  see: https://en.wikipedia.org/wiki/Box-drawing_character
* 
*  For this to work, we need to:
*  1. use the std::wcout function. This requires using wide chars for all screen output.
*  2. set the screen mode using the _setmode() function.
*/
int main()
{
	// Set the screen mode to support box characters
	// https://stackoverflow.com/questions/4882031/displaying-extended-ascii-characters
	auto result = _setmode(_fileno(stdout), _O_U8TEXT);
	if (result == -1) {
		std::cout << "Cannot set box drawing mode" << std::endl;
		return -1;
	}

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
		std::wstring guess_string(L"");
		std::getline(std::wcin, guess_string);
		if ((guess_string == L"Q") || (guess_string == L"q")) {
			game.quit_game();
			break;
		}

		// submit user guess
		if (!game.submit_next_guess(guess_string))
			std::wcout << L'\a';
	}

	display.Draw(game);
	std::cin.get();
}
