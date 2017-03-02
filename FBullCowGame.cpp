/*
BullCowGame class. Functionality of the game is developed here.
*/
#pragma once
#include "FBullCowGame.h"
#include "MessagePrinter.h"
#include <map>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#define TMap std::map

// Unreal friendly
using FString = std::string;
using int32 = int;

// constructor
FBullCowGame::FBullCowGame() { Reset(); }

// getters
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }

// setters
void FBullCowGame::SetDifficulty(int32 SelectedDifficulty) { Difficulty = SelectedDifficulty; }

// reseting game settings for new game
void FBullCowGame::Reset()
{
	MyHiddenWord = "";
	MyCurrentTry = 1;
	bIsGameWon = false;
}

// asking and setting game difficulty + choosing hidden word based on chosen difficulty
void FBullCowGame::SetParameters()
{
	AskDifficulty();
	MyHiddenWord = RandomHiddenWordChoice();
}

// calculates&returns max tries depending on word length
int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries = { { 3,8 },{ 4,15 },{ 5,19 },{ 6,23 },{ 7,27 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

// checks user's guess for errors
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else {
		return EGuessStatus::OK;
	}
}

// receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Word)
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	// traverse hidden word
	for (int32 i = 0; i < WordLength; i++) {
		// traverse guess
		for (int32 j = 0; j < WordLength; j++) {
			// compare characters
			if (MyHiddenWord[i] == Word[j]) {
				// same position
				if (i == j) {
					BullCowCount.Bulls++;
				}
				// different position
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
	}

	return BullCowCount;
}

// receives a guess and determines whether it is an isogram or not
bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LettersSeen;

	for (auto Letter : Guess) {
		Letter = tolower(Letter);
		if (LettersSeen[Letter]) {
			return false;
		}
		else {
			LettersSeen[Letter] = true;
		}
	}

	return true;
}

// receives a guess and determines whether it is lowercase or not
bool FBullCowGame::IsLowerCase(FString Guess) const
{
	if (Guess.length() < 1) {
		return true;
	}

	for (auto Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

// ask user for difficulty/word length
void FBullCowGame::AskDifficulty() {
	TMap<int32, int32> DifficultyToWordLength = { { 1,3 },{ 2,4 } ,{ 3,5 } ,{ 4,6 } ,{ 5,7 } };
	TMap<int32, FString> ChoiceToDifficulty = {
		{ 1,"Very Easy" },
		{ 2,"Easy" },
		{ 3,"Normal" },
		{ 4,"Hard" },
		{ 5,"Very Hard" }
	};
	// print menu for difficulty selection
	MessagePrinter::DifficultyMenu();

	FString Choice = "";
	int32 ChosenDifficulty;
	do {
		// get user choice
		std::getline(std::cin, Choice);
		// cast to integer
		ChosenDifficulty = std::stoi(Choice);
		if (!(ChosenDifficulty > 0 && ChosenDifficulty < 6)) {
			std::cout << "Choose proper difficulty!\n";
		}
	} while (ChosenDifficulty && !(ChosenDifficulty > 0 && ChosenDifficulty < 6));

	// set difficulty
	SetDifficulty(ChosenDifficulty);

	std::cout << "\"" << ChoiceToDifficulty[ChosenDifficulty] << "\" chosen - Playing with " << DifficultyToWordLength[Difficulty] << " letter words\n";
	
}

// a random word is selected according to chosen difficulty
// opening appropriate txt file from resources
FString FBullCowGame::RandomHiddenWordChoice()
{
	FString FileName = "diff_" + std::to_string(Difficulty) + "_words.txt";
	std::ifstream WordFile(FileName);
	
	if (!WordFile) {
		std::cout << "Cannot open input file.\n";
		return 0;
	}

	FString RandomlySelectedHiddenWord = "";
	// calulating the number of lines on the file (number of lines = number of words)
	int32 NumberOfWords;
	NumberOfWords = std::count(std::istreambuf_iterator<char>(WordFile), std::istreambuf_iterator<char>(), '\n');
	// reseting file scan
	WordFile.clear();
	WordFile.seekg(0, WordFile.beg);

	// initialize seed
	srand(time(NULL));
	// select random word
	int32 RandomIndex = rand() % NumberOfWords + 1;
	for (int i = 0; i < RandomIndex; i++) {
		//std::cout << i;
		getline(WordFile, RandomlySelectedHiddenWord);
	}
	
	WordFile.close();

	return RandomlySelectedHiddenWord;
}
