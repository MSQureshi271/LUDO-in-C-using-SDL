#include<SDL2/SDL.h>
#include<math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)
#define DICE_SIZE 100  // Size of the dice square
#define DOT_SIZE 15    // Size of each dot on the dice

// Helper function to draw a filled circle for rounded corners
void drawFilledCircle(SDL_Renderer *renderer, int cx, int cy, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;  // Horizontal distance to center
            int dy = radius - h;  // Vertical distance to center
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

// Function to draw a dice with rounded corners based on the rolled dice number
void drawDice(SDL_Renderer *renderer, int diceNumber, int x, int y) {
    int cornerRadius = 20;  // Radius for rounded corners

    // Draw the main square background with rounded corners
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White for dice background
    SDL_Rect mainRect = {x + cornerRadius, y, DICE_SIZE - 2 * cornerRadius, DICE_SIZE};
    SDL_RenderFillRect(renderer, &mainRect);
    mainRect = (SDL_Rect){x, y + cornerRadius, DICE_SIZE, DICE_SIZE - 2 * cornerRadius};
    SDL_RenderFillRect(renderer, &mainRect);

    // Draw the rounded corners as filled circles
    drawFilledCircle(renderer, x + cornerRadius, y + cornerRadius, cornerRadius);              // Top-left corner
    drawFilledCircle(renderer, x + DICE_SIZE - cornerRadius, y + cornerRadius, cornerRadius);  // Top-right corner
    drawFilledCircle(renderer, x + cornerRadius, y + DICE_SIZE - cornerRadius, cornerRadius);  // Bottom-left corner
    drawFilledCircle(renderer, x + DICE_SIZE - cornerRadius, y + DICE_SIZE - cornerRadius, cornerRadius);  // Bottom-right corner

    // Set color for dice dots
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black for dice dots

    int centerX = x + DICE_SIZE / 2 - DOT_SIZE / 2;
    int centerY = y + DICE_SIZE / 2 - DOT_SIZE / 2;
    int offsetX = DICE_SIZE / 4;
    int offsetY = DICE_SIZE / 4;

    // Draw dots based on the dice number
    switch (diceNumber) {
        case 1:
            SDL_RenderFillRect(renderer, &(SDL_Rect){centerX, centerY, DOT_SIZE, DOT_SIZE});
            break;
        case 2:
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            break;
        case 3:
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){centerX, centerY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            break;
        case 4:
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            break;
        case 5:
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){centerX, centerY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            break;
        case 6:
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, centerY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, centerY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            break;
    }
}
