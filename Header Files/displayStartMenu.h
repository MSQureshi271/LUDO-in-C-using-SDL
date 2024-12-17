#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "renderText.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

// Function to display start menu
int displayStartMenu(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_Surface *bgSurface = IMG_Load("Images/background.jpg"); // Load the image
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

    SDL_Color buttonColor = {194, 152, 70, 255}; // Brown Shade Color
    SDL_Color buttonHoverColor = {219, 176, 92, 255}; // Slightly Lighter Brown Color for hover effect
    SDL_Color textColor = {0, 0, 0, 255}; // Black Text

    SDL_Rect twoPlayersButton = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 10, 200, 50};
    SDL_Rect threePlayersButton = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 70, 200, 50};
    SDL_Rect fourPlayersButton = {SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 150, 200, 50};

    int selectedPlayers = 0;
    int running = 1;

    while (running) {
        SDL_Event event;
        int mouseX, mouseY;
        SDL_Color currentButtonColor;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                break;
            }
            if (event.type == SDL_MOUSEMOTION) {
                mouseX = event.motion.x;
                mouseY = event.motion.y;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                mouseX = event.button.x;
                mouseY = event.button.y;

                if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &twoPlayersButton)) {
                    selectedPlayers = 2;
                    running = 0;
                } else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &threePlayersButton)) {
                    selectedPlayers = 3;
                    running = 0;
                } else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &fourPlayersButton)) {
                    selectedPlayers = 4;
                    running = 0;
                }
            }
        }

        // Render the background image
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

        // Render the buttons
        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &twoPlayersButton)) {
            currentButtonColor = buttonHoverColor;
        } else {
            currentButtonColor = buttonColor;
        }
        SDL_SetRenderDrawColor(renderer, currentButtonColor.r, currentButtonColor.g, currentButtonColor.b, 255);
        SDL_RenderFillRect(renderer, &twoPlayersButton);
        renderText(renderer, "2 Players", twoPlayersButton, textColor, font);

        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &threePlayersButton)) {
            currentButtonColor = buttonHoverColor;
        } else {
            currentButtonColor = buttonColor;
        }
        SDL_SetRenderDrawColor(renderer, currentButtonColor.r, currentButtonColor.g, currentButtonColor.b, 255);
        SDL_RenderFillRect(renderer, &threePlayersButton);
        renderText(renderer, "3 Players", threePlayersButton, textColor, font);

        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &fourPlayersButton)) {
            currentButtonColor = buttonHoverColor;
        } else {
            currentButtonColor = buttonColor;
        }
        SDL_SetRenderDrawColor(renderer, currentButtonColor.r, currentButtonColor.g, currentButtonColor.b, 255);
        SDL_RenderFillRect(renderer, &fourPlayersButton);
        renderText(renderer, "4 Players", fourPlayersButton, textColor, font);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(bgTexture);
    return selectedPlayers;
}
