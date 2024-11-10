#include<SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)

// Function to draw tokens in the players' home zones
void drawTokens(SDL_Renderer *renderer) {
    SDL_Color redToken = {150, 0, 0, 255};
    SDL_Color greenToken = {0, 150, 0, 255};
    SDL_Color blueToken = {0, 0, 150, 255};
    SDL_Color yellowToken = {150, 150, 0, 255};

    SDL_Rect token = {0, 0, CELL_SIZE / 2, CELL_SIZE / 2};
    SDL_Rect outline = {0, 0, CELL_SIZE / 2 + 2, CELL_SIZE / 2 + 2};
    int separation = 3;

    // Player 1 (Red) tokens
    int redX = 1 * CELL_SIZE + separation;
    int redY = 1 * CELL_SIZE + separation;
    for (int i = 0; i < 4; ++i) {
        token.x = redX + (i % 2) * (CELL_SIZE / 2 + separation);
        token.y = redY + (i / 2) * (CELL_SIZE / 2 + separation);
        outline.x = token.x - 1;
        outline.y = token.y - 1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &outline);
        SDL_SetRenderDrawColor(renderer, redToken.r, redToken.g, redToken.b, redToken.a);
        SDL_RenderFillRect(renderer, &token);
    }

    // Player 2 (Green) tokens
    int greenX = 9 * CELL_SIZE + separation;
    int greenY = 1 * CELL_SIZE + separation;
    for (int i = 0; i < 4; ++i) {
        token.x = greenX + (i % 2) * (CELL_SIZE / 2 + separation);
        token.y = greenY + (i / 2) * (CELL_SIZE / 2 + separation);
        outline.x = token.x - 1;
        outline.y = token.y - 1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &outline);
        SDL_SetRenderDrawColor(renderer, greenToken.r, greenToken.g, greenToken.b, greenToken.a);
        SDL_RenderFillRect(renderer, &token);
    }

    // Player 3 (Blue) tokens
    int blueX = 1 * CELL_SIZE + separation;
    int blueY = 9 * CELL_SIZE + separation;
    for (int i = 0; i < 4; ++i) {
        token.x = blueX + (i % 2) * (CELL_SIZE / 2 + separation);
        token.y = blueY + (i / 2) * (CELL_SIZE / 2 + separation);
        outline.x = token.x - 1;
        outline.y = token.y - 1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &outline);
        SDL_SetRenderDrawColor(renderer, blueToken.r, blueToken.g, blueToken.b, blueToken.a);
        SDL_RenderFillRect(renderer, &token);
    }

    // Player 4 (Yellow) tokens
    int yellowX = 9 * CELL_SIZE + separation;
    int yellowY = 9 * CELL_SIZE + separation;
    for (int i = 0; i < 4; ++i) {
        token.x = yellowX + (i % 2) * (CELL_SIZE / 2 + separation);
        token.y = yellowY + (i / 2) * (CELL_SIZE / 2 + separation);
        outline.x = token.x - 1;
        outline.y = token.y - 1;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &outline);
        SDL_SetRenderDrawColor(renderer, yellowToken.r, yellowToken.g, yellowToken.b, yellowToken.a);
        SDL_RenderFillRect(renderer, &token);
    }
}