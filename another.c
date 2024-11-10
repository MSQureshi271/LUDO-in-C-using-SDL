#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "drawBoard.h"
#include "drawTokens.h"
#include "drawDice.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)
#define DICE_SIZE 100  // Size of the dice square
#define DOT_SIZE 15    // Size of each dot on the dice

// Function to roll the dice
int rollDice() {
    return (rand() % 6) + 1;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    srand(time(NULL));

    SDL_Window *window = SDL_CreateWindow("Ludo Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == NULL || renderer == NULL) {
        printf("Could not create window or renderer! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    int running = 1;
    SDL_Event event;
    int diceResult = rollDice();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                diceResult = rollDice();  // Roll dice on key press
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawLudoBoard(renderer);
        drawTokens(renderer);  // Draw tokens for each player's zone

        // Draw dice in the center area
        int diceX = 7 * CELL_SIZE + (CELL_SIZE / 2) - (DICE_SIZE / 2);
        int diceY = 7 * CELL_SIZE + (CELL_SIZE / 2) - (DICE_SIZE / 2);
        drawDice(renderer, diceResult, diceX, diceY);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}