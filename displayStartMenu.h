#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

// Function to render text using SDL_ttf
void renderText(SDL_Renderer *renderer, const char *text, SDL_Rect rect, SDL_Color color, TTF_Font *font) {
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
    if (!textSurface) {
        printf("Unable to create text surface: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    if (!textTexture) {
        printf("Unable to create text texture: %s\n", SDL_GetError());
        return;
    }

    SDL_RenderCopy(renderer, textTexture, NULL, &rect);
    SDL_DestroyTexture(textTexture);
}

// Function to display start menu
int displayStartMenu(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_Color buttonColor = {100, 100, 255, 255};  // Blue buttons
    SDL_Color buttonHoverColor = {150, 150, 255, 255}; // Light blue for hover effect
    SDL_Color textColor = {255, 255, 255, 255};    // White text

    SDL_Rect menuHeading = {SCREEN_WIDTH / 2 - 100, 50, 200, 50};
    SDL_Rect twoPlayersButton = {SCREEN_WIDTH / 2 - 100, 150, 200, 50};
    SDL_Rect threePlayersButton = {SCREEN_WIDTH / 2 - 100, 250, 200, 50};
    SDL_Rect fourPlayersButton = {SCREEN_WIDTH / 2 - 100, 350, 200, 50};

    int selectedPlayers = 0;
    int running = 1;

    while (running) {
        SDL_Event event;
        int mouseX, mouseY;
        SDL_Color currentButtonColor;

        // Event handling
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

                // Check if the user clicked on any button
                if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &twoPlayersButton)) {
                    selectedPlayers = 2;
                    running = 0;  // Exit menu
                } else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &threePlayersButton)) {
                    selectedPlayers = 3;
                    running = 0;
                } else if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &fourPlayersButton)) {
                    selectedPlayers = 4;
                    running = 0;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(renderer);

        // Render "LUDO Game" heading with different colors for L, U, D, O
        SDL_Rect letterRect = {SCREEN_WIDTH / 2 - 100, 50, 40, 50};
        
        SDL_Color colors[] = { {255, 0, 0, 255}, {255, 255, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255} };
        const char *letters[] = { "L", "U", "D", "O" };

        for (int i = 0; i < 4; i++) {
            renderText(renderer, letters[i], letterRect, colors[i], font);
            letterRect.x += 50;  // Move the position for the next letter
        }

        // Render 2 Players button
        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &twoPlayersButton)) {
            currentButtonColor = buttonHoverColor;
        } else {
            currentButtonColor = buttonColor;
        }
        SDL_SetRenderDrawColor(renderer, currentButtonColor.r, currentButtonColor.g, currentButtonColor.b, 255);
        SDL_RenderFillRect(renderer, &twoPlayersButton);
        renderText(renderer, "2 Players", twoPlayersButton, textColor, font);

        // Render 3 Players button
        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &threePlayersButton)) {
            currentButtonColor = buttonHoverColor;
        } else {
            currentButtonColor = buttonColor;
        }
        SDL_SetRenderDrawColor(renderer, currentButtonColor.r, currentButtonColor.g, currentButtonColor.b, 255);
        SDL_RenderFillRect(renderer, &threePlayersButton);
        renderText(renderer, "3 Players", threePlayersButton, textColor, font);

        // Render 4 Players button
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

    return selectedPlayers;
}
