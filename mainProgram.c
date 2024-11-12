#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "drawBoard.h"
#include "drawTokens.h"
#include "displayStartMenu.h"
#include "rollDice.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)
#define DICE_SIZE 100  // Size of the dice square
#define DOT_SIZE 15    // Size of each dot on the dice

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

    TTF_Init(); //Initialize SDL_TTF
    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);  // Load the font
    if (!font) {
        printf("Unable to load font: %s\n", TTF_GetError());
        return -1;
    }

    int numPlayers = displayStartMenu(renderer, font);

    SDL_RenderClear(renderer);

    int running = 1;
    SDL_Event event;
    int diceResult;

    // Coordinates to draw the dice in the center area
    int diceX = 7 * CELL_SIZE + (CELL_SIZE / 2) - (DICE_SIZE / 2);
    int diceY = 7 * CELL_SIZE + (CELL_SIZE / 2) - (DICE_SIZE / 2);

    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                // Roll dice with shuffling effect when Enter is pressed
                diceResult = rollDice(renderer, diceX, diceY);
            }
        }

        // Clear screen and redraw game elements
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        drawLudoBoard(renderer);

        if (numPlayers >= 2 && numPlayers <= 4) {
            drawTokens(renderer, numPlayers);
        }

        // Draw final dice result in the center
        drawDice(renderer, diceResult, diceX, diceY);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
