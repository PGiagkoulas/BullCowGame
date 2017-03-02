/*
Helper class containing methods for screen messages
*/

#pragma once
#include "MessagePrinter.h"
#include <string>
#include <iostream>
#include <map>

#define TMap std::map

// Unreal friendly
using FString = std::string;
using int32 = int;

namespace MessagePrinter {
	// game intro screen
	void IntroScreen()
	{
		std::cout << "/~~~~~~~~~~~~Bulls & Cows~~~~~~~~~~~~~\\\n";
		std::cout << std::endl;
		std::cout << "          }   {         ___ " << std::endl;
		std::cout << "          (o o)        (o o) " << std::endl;
		std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
		std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
		std::cout << " *  |-,--- |              |------|  * " << std::endl;
		std::cout << "    ^      ^              ^      ^ " << std::endl;
		std::cout << std::endl;
		std::cout << "\\____Guess the isogram word game!____/\n";
		std::cout << std::endl;
	}

	// difficulty selection menu
	void DifficultyMenu() {
		TMap<int32, FString> ChoiceToDifficulty = {
			{ 1,"Very Easy" },
			{ 2,"Easy" },
			{ 3,"Normal" },
			{ 4,"Hard" },
			{ 5,"Very Hard" }
		};
		std::cout << "Choose difficulty level:\n";
		for (int32 i = 1; i <= ChoiceToDifficulty.size(); i++) {
			std::cout << i << "." << ChoiceToDifficulty[i] << "\n";
		}
	}

	// game rules
	void PrintRules() {
		std::cout << "~~~~~~~~~~~~~How To Play~~~~~~~~~~~~~\n";
		std::cout << "Bulls and Cows is a word guessing game based on mastermind\n";
		std::cout << "After choosing difficulty you will start guessing the hidden word\n";
		std::cout << "The words in the game are isograms, which means no letter is used twise to form the word!\n";
		std::cout << "Each time you submit a guess you get feedback, represented as Bulls and Cows\n";
		std::cout << "A \"Bull\" means a letter in your guess is in the hidden word and in the same position\n";
		std::cout << "A \"Cow\" means a letter in your guess is in the hidden word but at a different position\n";
		std::cout << "The moment you hit all the \"Bulls\" you win!\n";
		std::cout << "____________How To Play______________\n";
	}

	// message prompting the user to continue
	void PrintPromptToContinue()
	{
		std::cout << std::endl;
		system("pause");
		std::cout << std::endl;
	}
}