#include <SDL2/SDL.h>
#include "drawLudoBoard.h"
#include "drawTokens.h"

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
int currentPlayer = 0;

// Player paths
SDL_Point paths[4][56] = {
    { // Red's Path
        {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 5}, {6, 4}, {6, 3}, {6, 2}, {6, 1},
        {6, 0}, {7, 0}, {8, 0}, {8, 1}, {8, 2}, {8, 3}, {8, 4}, {8, 5}, {9, 6}, {10, 6},
        {11, 6}, {12, 6}, {13, 6}, {14, 6}, {14, 7}, {14, 8}, {13, 8}, {12, 8}, {11, 8}, {10, 8},
        {9, 8}, {8, 9}, {8, 10}, {8, 11}, {8, 12}, {8, 13}, {8, 14}, {7, 14}, {6, 14}, {6, 13},
        {6, 12}, {6, 11}, {6, 10}, {6, 9}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 8},
        {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}
    },
    { //Yellow's Path
        {13, 8}, {12, 8}, {11, 8}, {10, 8}, {9, 8}, {8, 9}, {8, 10}, {8, 11}, {8, 12}, {8, 13},
        {8, 14}, {7, 14}, {6, 14}, {6, 13}, {6, 12}, {6, 11}, {6, 10}, {6, 9}, {5, 8}, {4, 8},
        {3, 8}, {2, 8}, {1, 8}, {0, 8}, {0, 7}, {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6},
        {5, 6}, {6, 5}, {6, 4}, {6, 3}, {6, 2}, {6, 1}, {6, 0}, {7, 0}, {8, 0}, {8, 1},
        {8, 2}, {8, 3}, {8, 4}, {8, 5}, {9, 6}, {10, 6}, {11, 6}, {12, 6}, {13, 6}, {14, 6},
        {14, 7}, {13, 7}, {12, 7}, {11, 7}, {10, 7}, {9, 7}
    },
    { //Blue's Path
        {6, 13}, {6, 12}, {6, 11}, {6, 10}, {6, 9}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8},
        {0, 8}, {0, 7}, {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 5}, {6, 4},
        {6, 3}, {6, 2}, {6, 1}, {6, 0}, {7, 0}, {8, 0}, {8, 1}, {8, 2}, {8, 3}, {8, 4},
        {8, 5}, {9, 6}, {10, 6}, {11, 6}, {12, 6}, {13, 6}, {14, 6}, {14, 7}, {14, 8}, {13, 8},
        {12, 8}, {11, 8}, {10, 8}, {9, 8}, {8, 9}, {8, 10}, {8, 11}, {8, 12}, {8, 13}, {8, 14},
        {7, 14}, {7, 13}, {7, 12}, {7, 11}, {7, 10}, {7, 9}
    },
    { //Green's Path
        {8, 1}, {8, 2}, {8, 3}, {8, 4}, {8, 5}, {9, 6}, {10, 6}, {11, 6}, {12, 6}, {13, 6},
        {14, 6}, {14, 7}, {14, 8}, {13, 8}, {12, 8}, {11, 8}, {10, 8}, {9, 8}, {8, 9}, {8, 10},
        {8, 11}, {8, 12}, {8, 13}, {8, 14}, {7, 14}, {6, 14}, {6, 13}, {6, 12}, {6, 11}, {6, 10},
        {6, 9}, {5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 8}, {0, 7}, {0, 6}, {1, 6}, {2, 6},
        {3, 6}, {4, 6}, {5, 6}, {6, 5}, {6, 4}, {6, 3}, {6, 2}, {6, 1}, {6, 0}, {7, 0}, {7, 1},
        {7, 2}, {7, 3}, {7, 4}, {7, 5}
    }
};


//Animate the tokens to move
void animateToken(Token *token, SDL_Point target, SDL_Renderer *renderer) {
    int targetX = (target.x + 0.5) * CELL_SIZE;
    int targetY = (target.y + 0.5) * CELL_SIZE;
    int steps = 3; // Number of animation steps for smoothness
    float dx = (targetX - token->x) / (float)steps;
    float dy = (targetY - token->y) / (float)steps;

    for (int i = 0; i < steps; i++) {
        token->x += dx;
        token->y += dy;

        // Redraw the board and tokens for animation
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        drawLudoBoard(renderer);
        drawTokens(renderer, 4, 0, currentPlayer); // Adjust parameters as needed
        SDL_RenderPresent(renderer);

        SDL_Delay(20); // Delay for smoother animation (20ms per step)
    }

    // Ensure the token ends exactly at the target position
    token->x = targetX;
    token->y = targetY;
}
