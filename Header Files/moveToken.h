#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)
#include "displayWinner.h"
#include "drawLudoBoard.h"
#include "isSafeGrid.h"
#include "drawTokens.h"
#include "animateToken.h"

// Structure for tokens
typedef struct {
    int x, y;           // Current position
    int isHome;         // 1 if in home zone, 0 otherwise
    int player;         // Player ID
    int index;          // Token index
} Token;


// Token storage for 4 players, each with 4 tokens
Token tokens[4][4];

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

int running = 1;
int currentPlayer = 0;   // Track the current player's turn
int diceResult = 0;      // Store the dice roll result
int selectedToken = -1;  // Track the currently selected token (-1 if none)
int isDiceRolled = 0;    // Flag to ensure dice roll before moving a token

static int tokenPositions[4][4] = {{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}};

// Function to move the token
void moveToken(Token *token, int diceRoll, int currentPlayer, SDL_Renderer *renderer, TTF_Font *font) {
    if (token->isHome && diceRoll == 6) {
        // Move token out of home
        token->isHome = 0;
        tokenPositions[currentPlayer][token->index] = 0; // Set to the start of the path
        SDL_Point startPos = paths[currentPlayer][0];
        animateToken(token, startPos, renderer); // Animate token to the start position
    } else if (!token->isHome) {
        // Calculate new position
        int *currentPos = &tokenPositions[currentPlayer][token->index];
        int newPos = *currentPos + diceRoll;

        if (newPos == 56) { // Exact win condition
            *currentPos = newPos;
            SDL_Point newPosPoint = paths[currentPlayer][newPos];
            animateToken(token, newPosPoint, renderer); // Animate to the final position
            displayWinner(renderer, currentPlayer, font); // Announce the winner
            running = 0; // Terminate the game
            return;
        } else if (newPos < 56) { // Move only if not overshooting
            // Animate step-by-step to each position
            for (int step = *currentPos + 1; step <= newPos; ++step) {
                SDL_Point stepPoint = paths[currentPlayer][step];
                animateToken(token, stepPoint, renderer);
            }
            *currentPos = newPos;

            // Check for collisions
            for (int i = 0; i < 4; i++) { // Iterate over all other players
                if (i != currentPlayer) {
                    for (int j = 0; j < 4; j++) {
                        Token *otherToken = &tokens[i][j];

                        // Skip checking tokens that are still in their home zones
                        if (otherToken->isHome) continue;

                        // Check if the other token is at the same position
                        if (otherToken->x == token->x && otherToken->y == token->y) {
                            // Check if the position is a safe grid
                            int gridX = otherToken->x / CELL_SIZE;
                            int gridY = otherToken->y / CELL_SIZE;

                            if (isSafeGrid(gridX, gridY)) {
                                // Token on a safe grid is protected and cannot be captured
                                continue;
                            }

                            // Send the other token back to its home
                            otherToken->isHome = 1;
                            tokenPositions[i][j] = -1; // Reset its position
                            
                            // Place the token back in its home zone
                            SDL_Point homeZones[4] = {
                                {2, 2},  // Red
                                {12, 12},// Yellow
                                {2, 12}, // Blue
                                {12, 2}  // Green
                            };

                            int homeX = homeZones[i].x * CELL_SIZE;
                            int homeY = homeZones[i].y * CELL_SIZE;
                            int spacing = CELL_SIZE / 4;

                            otherToken->x = homeX + (j % 2) * (CELL_SIZE / 2 + spacing);
                            otherToken->y = homeY + (j / 2) * (CELL_SIZE / 2 + spacing);

                            break; // Only one token can occupy the spot
                        }
                    }
                }
            }
        }
    }
}