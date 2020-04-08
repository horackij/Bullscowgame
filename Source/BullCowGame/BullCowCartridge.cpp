// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame();
    
    //Welcome the player
    PrintLine(TEXT("Welcome to Cows and Bulls!"));
    PrintLine(TEXT("Guess the 4 letter word"));  //Magic number remove
    PrintLine(TEXT("Press Enter to continue...."));

    //Prompt Player for Guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();

    
    //Checking Player Guess
    PrintLine(Input);
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("You have Won!"));
    }
    else
    {
        PrintLine(TEXT("You have Lost!"));
        if (Input.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("Wrong number of characters"));
        }
    }
}

void UBullCowCartridge::SetupGame()
{
        HiddenWord = TEXT("oneway");  
        Lives = 4; 
}

    //Check if Isogram
    //Prompt to Guess again
    //check right number of letters
    //Prompt to guess again

    //Remove a life

    //Check if Lives > 0
    //If Yes guess Again
    //Show lives left
    //if no show gameover and HiddenWord
    //Prompt to play again, Press Enter to Play Again?
    //Check user Input
    //Play Again or quit
