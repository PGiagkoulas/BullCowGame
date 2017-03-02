#pragma once
#include <string>

// Unreal friendly
using FString = std::string;
using int32 = int;

// all values initialized to zero
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	FString GetHiddenWord() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	void SetParameters();
	void SetDifficulty(int32);
	FBullCowCount SubmitValidGuess(FString);

	
private:
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
	void AskDifficulty();
	FString RandomHiddenWordChoice();

	int32 MyCurrentTry;
	int32 Difficulty;
	FString MyHiddenWord;
	bool bIsGameWon;
};