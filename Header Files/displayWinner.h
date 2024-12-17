#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "renderText.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

//Function to display winner at End Screen
void displayWinner(SDL_Renderer *renderer, int winner, TTF_Font *font) {
    // Load the background image
    SDL_Surface *bgSurface = IMG_Load("Images/winner_background.jpg"); // Replace with your image path
    if (!bgSurface) {
        printf("Unable to load background image: %s\n", SDL_GetError());
        return;
    }
    SDL_Texture *bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    if (!bgTexture) {
        printf("Unable to create texture from background image: %s\n", SDL_GetError());
        return;
    }

    char winnerText[50];
    sprintf(winnerText, "Player %d Wins!", winner + 1); // Format the winner's message

    // Define player colors
    SDL_Color playerColors[4] = {
        {255, 0, 0, 255},    // Red
        {255, 255, 0, 255},  // Yellow
        {0, 0, 255, 255},    // Blue
        {0, 255, 0, 255}     // Green
    };

    SDL_Color textColor = playerColors[winner]; // Use the winner's color
    SDL_Rect textRect = {SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 70, 300, 100};

    // Render the background image
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

    // Render the winner text
    renderText(renderer, winnerText, textRect, textColor, font);

    SDL_RenderPresent(renderer);

    // Pause to let the winner announcement stay visible
    SDL_Delay(5000); // Wait for 5 seconds

    SDL_DestroyTexture(bgTexture); // Clean up texture
}
