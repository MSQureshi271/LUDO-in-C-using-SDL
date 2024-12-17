#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)
#define TOKEN_RADIUS (CELL_SIZE / 3)
#define OUTLINE_RADIUS (TOKEN_RADIUS+2)

// Structure for tokens
typedef struct {
    int x, y;           // Current position
    int isHome;         // 1 if in home zone, 0 otherwise
    int player;         // Player ID
    int index;          // Token index
} Token;


// Token storage for 4 players, each with 4 tokens
Token tokens[4][4];

int currentPlayer = 0;   // Track the current player's turn
int diceResult = 0;      // Store the dice roll result

// Function to detect token selection
int handleTokenSelection(SDL_Event *event, int currentPlayer) {
    if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT) {
        int mouseX = event->button.x;
        int mouseY = event->button.y;

        for (int i = 0; i < 4; i++) {
            Token *token = &tokens[currentPlayer][i];
            // Allow selection if the token can move (freed or can be freed)
            if (!token->isHome || (token->isHome && diceResult == 6)) {
                if (abs(mouseX - token->x) < TOKEN_RADIUS && abs(mouseY - token->y) < TOKEN_RADIUS) {
                    return i; // Return the selected token index
                }
            }
        }
    }
    return -1; // No valid token selected
}