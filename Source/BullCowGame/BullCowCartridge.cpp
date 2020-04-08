// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame();
    
    PrintLine(FString::Printf(TEXT("The Hidden Word is : %s"), *HiddenWord));  // Debug line
 }

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input); //Checking Player Guess
    }   
}

void UBullCowCartridge::SetupGame()
{
        HiddenWord = TEXT("oneway");  
        Lives = HiddenWord.Len(); 
        bGameOver = false;
        
        //Welcome the player
        PrintLine(TEXT("Welcome to Cows and Bulls!"));
        PrintLine(FString::Printf(TEXT("Guess the %i letter word"), HiddenWord.Len()));  //Magic number remove
        PrintLine(FString::Printf(TEXT("You have %i Lives"), Lives));
        PrintLine(TEXT("Type your Guess and press Enter to continue...."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
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
        PrintLine(TEXT("Incorrect!\n"));
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

bool UBullCowCartridge::IsIsogram(FString Word) const
{

    return true;}


void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play Again."));
}

