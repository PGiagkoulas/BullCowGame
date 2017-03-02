#pragma once
#include <iostream>
#include <string>
#include <map>
#include "FBullCowGame.h"
#include "MessagePrinter.h"

#define TMap std::map

// Unreal friendly
using FText = std::string;
using int32 = int;

void PlayGame();
FText GetValidGuess();
bool AskReplay();
void PrintGameSummary();

FBullCowGame BCGame;

int main()
{
	MessagePrinter::IntroScreen();
	MessagePrinter::PrintRules();
	MessagePrinter::PrintPromptToContinue();
	do {
		PlayGame();
	}
	while(AskReplay());
	
	return 0;
}

// game procedure
void PlayGame()
{
	BCGame.Reset();
	BCGame.SetParameters();
	std::cout << "Game Begins!\n";
	int32 MaxTries = BCGame.GetMaxTries();
	FText Guess = "";

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) {
		Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << " - Cows: " << BullCowCount.Cows << std::endl << std::endl;
	}

	PrintGameSummary();
}

// taking user's guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		Guess = "";

		std::cout << "Try no." << CurrentTry << " of " << BCGame.GetMaxTries() << " | Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Guess should not be an isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Guess should be written in lowercase.\n\n";
			break;
		default:
			//std::cout << "Valid guess";
			break;
		}
	} while (Status != EGuessStatus::OK);
	
	return Guess;
}

bool AskReplay()
{
	std::cout << "Wanna play again (y/n)?  ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (tolower(Response[0]) == 'y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "You won!\n";
		std::cout << "You found the word: \"" << BCGame.GetHiddenWord() << "\" in " << BCGame.GetCurrentTry()-1 << " tries\n";
	}
	else {
		std::cout << "You failed\n";
		std::cout << "The word you were looking for was: " << BCGame.GetHiddenWord() << std::endl;
	}
	std::cout << std::endl << std::endl;
}
