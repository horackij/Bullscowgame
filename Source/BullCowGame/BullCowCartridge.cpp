// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

    SetupGame();
    
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(PlayerInput); //Checking Player Guess
    }   
}

void UBullCowCartridge::SetupGame()
{
        HiddenWord = Isograms[FMath::RandRange(0,Isograms.Num()-1)];
        Lives = HiddenWord.Len(); 
        bGameOver = false;
        
        //Welcome the player
        PrintLine(TEXT("Welcome to Cows and Bulls!"));
        PrintLine(FString::Printf(TEXT("Guess the %i letter word"), HiddenWord.Len()));  //Magic number remove
        PrintLine(FString::Printf(TEXT("You have %i Lives"), Lives));
        PrintLine(TEXT("Type your Guess and press Enter to continue...."));
        PrintLine(FString::Printf(TEXT("The Hidden Word is : %s"), *HiddenWord));  // Debug line
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
        bGameOver = true;
        return;
    }
    
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(FString::Printf(TEXT("The word has %i characters"), HiddenWord.Len()));
        PrintLine(TEXT("Try again."));
        return;
    }

    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("There are no repeating characters.  Try Again."));
        return
;    }

    --Lives;
    if (Lives > 0 )
    {
       FBullCowCount Score = GetBullCows(Guess);

        PrintLine(TEXT("\nYou have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
        
        PrintLine(FString::Printf(TEXT("You have %i Lives Left"), Lives));
        PrintLine(TEXT("Try again."));
        return;
    }

    if (Lives == 0)
    {
        PrintLine(TEXT("You Have Lost!")); 
        EndGame();
    }   
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    int32 Index = 0;
    
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparision = Index + 1; Comparision < Word.Len(); Comparision++)
        {
            if (Word[Index] == Word[Comparision])
            {
                return false;
            }    
        }
    }
    return true;
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play Again."));
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <=8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);            
        }
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const  
{
    FBullCowCount Count;

    for(int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}