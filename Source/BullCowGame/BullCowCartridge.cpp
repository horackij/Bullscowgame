// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetupGame();
    
    PrintLine(FString::Printf(TEXT("The Hidden Word is : %s"), *HiddenWord));  // Debug line
 
    //Prompt Player for Guess
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
       //Checking Player Guess
        PrintLine(Input);
        if (Input == HiddenWord)
        {
            PrintLine(TEXT("You have Won!"));
            bGameOver = true;
        }
        else
        {
            if (Input.Len() != HiddenWord.Len())
            {
                PrintLine(FString::Printf(TEXT("The word has %i characters"), HiddenWord.Len()));
            }
            --Lives;
            if (Lives > 0 )
            {
                PrintLine(FString::Printf(TEXT("You have %i Lives Left"), Lives));
                PrintLine(TEXT("Try again."));
                
            }
            else
            {
                PrintLine(TEXT("You Have Lost!")); 
                EndGame();
                
            }
        }   
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

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press Enter to play Again."));
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
