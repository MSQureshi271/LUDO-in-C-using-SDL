#include<SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)

// Function to draw tokens in the players' home zones
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

void drawTokens(SDL_Renderer *renderer) {
    SDL_Color redToken = {150, 0, 0, 255};
    SDL_Color greenToken = {0, 150, 0, 255};
    SDL_Color blueToken = {0, 0, 150, 255};
    SDL_Color yellowToken = {150, 150, 0, 255};
    
    int tokenRadius = CELL_SIZE / 3;          // Increase token size
    int outlineRadius = tokenRadius + 2;      // Increase outline slightly to match new token size
    int separation = 15;

    // Player 1 (Red) tokens
    int redX = 1 * CELL_SIZE + separation;
    int redY = 1 * CELL_SIZE + separation;
    for (int i = 0; i < 4; ++i) {
        int centerX = redX + (i % 2) * (CELL_SIZE / 2 + separation) + tokenRadius;
        int centerY = redY + (i / 2) * (CELL_SIZE / 2 + separation) + tokenRadius;

        drawCircle(renderer, centerX, centerY, outlineRadius, (SDL_Color){0, 0, 0, 255});
        drawCircle(renderer, centerX, centerY, tokenRadius, redToken);
    }

    // Player 2 (Green) tokens
    int greenX = 9 * CELL_SIZE + separation;
    int greenY = 1 * CELL_SIZE + separation;
    for (int i = 0; i < 4; ++i) {
        int centerX = greenX + (i % 2) * (CELL_SIZE / 2 + separation) + tokenRadius;
        int centerY = greenY + (i / 2) * (CELL_SIZE / 2 + separation) + tokenRadius;

        drawCircle(renderer, centerX, centerY, outlineRadius, (SDL_Color){0, 0, 0, 255});
        drawCircle(renderer, centerX, centerY, tokenRadius, greenToken);
    }

    // Player 3 (Blue) tokens
    int blueX = 1 * CELL_SIZE + separation;
    int blueY = 9 * CELL_SIZE + separation;
    for (int i = 0; i < 4; ++i) {
        int centerX = blueX + (i % 2) * (CELL_SIZE / 2 + separation) + tokenRadius;
        int centerY = blueY + (i / 2) * (CELL_SIZE / 2 + separation) + tokenRadius;

        drawCircle(renderer, centerX, centerY, outlineRadius, (SDL_Color){0, 0, 0, 255});
        drawCircle(renderer, centerX, centerY, tokenRadius, blueToken);
    }

    // Player 4 (Yellow) tokens
    int yellowX = 9 * CELL_SIZE + separation;
    int yellowY = 9 * CELL_SIZE + separation;
    for (int i = 0; i < 4; ++i) {
        int centerX = yellowX + (i % 2) * (CELL_SIZE / 2 + separation) + tokenRadius;
        int centerY = yellowY + (i / 2) * (CELL_SIZE / 2 + separation) + tokenRadius;

        drawCircle(renderer, centerX, centerY, outlineRadius, (SDL_Color){0, 0, 0, 255});
        drawCircle(renderer, centerX, centerY, tokenRadius, yellowToken);
    }
}
