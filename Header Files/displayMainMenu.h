#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "renderText.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

//Display Main Menu
int displayMainMenu(SDL_Renderer *renderer, TTF_Font *font) {
    // Load the background image
    SDL_Surface *bgSurface = IMG_Load("Images/background.jpg"); // Replace with your image path
    if (!bgSurface) {
        printf("Unable to load background image: %s\n", SDL_GetError());
        return 0;
    }
    SDL_Texture *bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    if (!bgTexture) {
        printf("Unable to create texture from background image: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Color buttonColor = {194, 152, 70, 255};  // Brown Shade buttons
    SDL_Color buttonHoverColor = {219, 176, 92, 255}; // Light Brown color for hover effect
    SDL_Color textColor = {0, 0, 0, 255}; // Black text

    SDL_Rect startButton = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 10, 200, 50}; // Lowered position
    SDL_Rect quitButton = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 70, 200, 50}; // Lowered position

    int selectedOption = 0; // 1 for Start, 2 for Quit
    int running = 1;

    while (running) {
        SDL_Event event;
        int mouseX, mouseY;
        SDL_Color currentButtonColor;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                selectedOption = 2; // Quit by closing the window
                break;
            }
            if (event.type == SDL_MOUSEMOTION) {
                mouseX = event.motion.x;
                mouseY = event.motion.y;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                mouseX = event.button.x;
                mouseY = event.button.y;

                if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &startButton)) {
                    selectedOption = 1; // Start game
                    running = 0;
                } else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &quitButton)) {
                    selectedOption = 2; // Quit game
                    running = 0;
                }
            }
        }

        // Render the background image
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

        // Render Start Button
        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &startButton)) {
            currentButtonColor = buttonHoverColor;
        } else {
            currentButtonColor = buttonColor;
        }
        SDL_SetRenderDrawColor(renderer, currentButtonColor.r, currentButtonColor.g, currentButtonColor.b, 255);
        SDL_RenderFillRect(renderer, &startButton);
        renderText(renderer, "Start", startButton, textColor, font);

        // Render Quit Button
        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &quitButton)) {
            currentButtonColor = buttonHoverColor;
        } else {
            currentButtonColor = buttonColor;
        }
        SDL_SetRenderDrawColor(renderer, currentButtonColor.r, currentButtonColor.g, currentButtonColor.b, 255);
        SDL_RenderFillRect(renderer, &quitButton);
        renderText(renderer, "Quit", quitButton, textColor, font);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(bgTexture); // Clean up background texture
    return selectedOption;
}