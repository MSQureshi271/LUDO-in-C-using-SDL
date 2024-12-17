#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)

// Structure for tokens
typedef struct {
    int x, y;           // Current position
    int isHome;         // 1 if in home zone, 0 otherwise
    int player;         // Player ID
    int index;          // Token index
} Token;


// Token storage for 4 players, each with 4 tokens
Token tokens[4][4];

// Function to initialize tokens in home zones
void initializeTokens(int numPlayers) {
    SDL_Point homeZones[4] = {
        {2, 2},  // Red
        {12, 12},// Yellow
        {2, 12}, // Blue
        {12, 2}  // Green
    };

    int spacing = CELL_SIZE / 4; // Increase spacing between tokens

    for (int i = 0; i < numPlayers; i++) {
        int homeX = homeZones[i].x * CELL_SIZE;
        int homeY = homeZones[i].y * CELL_SIZE;

        for (int j = 0; j < 4; j++) {
            tokens[i][j].x = homeX + (j % 2) * (CELL_SIZE / 2 + spacing);
            tokens[i][j].y = homeY + (j / 2) * (CELL_SIZE / 2 + spacing);
            tokens[i][j].isHome = 1;
            tokens[i][j].player = i;
            tokens[i][j].index = j;
        }
    }
}
