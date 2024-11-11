#include<SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)
#define DICE_SIZE 100  // Size of the dice square
#define DOT_SIZE 15    // Size of each dot on the dice

//Function to draw dice based on the dice number rolled
void drawDice(SDL_Renderer *renderer, int diceNumber, int x, int y) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black for the dice border
    SDL_Rect diceRect = {x, y, DICE_SIZE, DICE_SIZE};
    SDL_RenderFillRect(renderer, &diceRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White for the dots

    int centerX = x + DICE_SIZE / 2 - DOT_SIZE / 2;
    int centerY = y + DICE_SIZE / 2 - DOT_SIZE / 2;
    int offsetX = DICE_SIZE / 4;
    int offsetY = DICE_SIZE / 4;

    switch (diceNumber) {
        case 1:
            SDL_RenderFillRect(renderer, &(SDL_Rect){centerX, centerY, DOT_SIZE, DOT_SIZE});
            break;
        case 2:
            // Diagonal dots
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            break;
        case 3:
            // Two diagonal dots and center dot
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){centerX, centerY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            break;
        case 4:
            // Four corner dots (adjusted for better symmetry)
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            break;
        case 5:
            // Four corner dots and center dot
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){centerX, centerY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            break;
        case 6:
            // Six dots in two vertical columns (adjusted)
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + offsetY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, centerY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + offsetX, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, centerY, DOT_SIZE, DOT_SIZE});
            SDL_RenderFillRect(renderer, &(SDL_Rect){x + DICE_SIZE - offsetX - DOT_SIZE, y + DICE_SIZE - offsetY - DOT_SIZE, DOT_SIZE, DOT_SIZE}); //lower right corner
            break;
    }
}