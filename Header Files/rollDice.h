#include "drawDice.h"

#define DICE_SIZE 100
#define DOT_SIZE 10

// Helper function to draw a filled circle
void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // Horizontal distance from center
            int dy = radius - h; // Vertical distance from center
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

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
