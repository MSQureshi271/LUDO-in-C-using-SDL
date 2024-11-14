#include<SDL2/SDL.h>
#include"drawDice.h"

// Function to roll the dice with a shuffling effect
int rollDice(SDL_Renderer *renderer, int x, int y) {
    int finalRoll = (rand() % 6) + 1;  // Determine the final dice number
    int shuffleRoll;                    // Variable to hold intermediate random rolls
    Uint32 startTime = SDL_GetTicks();  // Get the current time

    // Loop to display random numbers for 1 second
    while (SDL_GetTicks() - startTime < 1000) {  // Shuffle for 1 second
        shuffleRoll = (rand() % 6) + 1;  // Get a random number for shuffling

        // Draw the shuffled dice number in the designated area
        drawDice(renderer, shuffleRoll, x, y);  // Display shuffled dice number
        SDL_RenderPresent(renderer);
        
        SDL_Delay(100);  // Delay for 100ms to create a shuffling effect
    }

    // Draw the final rolled number
    drawDice(renderer, finalRoll, x, y);
    SDL_RenderPresent(renderer);

    return finalRoll;
}