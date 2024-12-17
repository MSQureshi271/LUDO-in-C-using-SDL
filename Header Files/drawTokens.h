#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
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

static int tokenPositions[4][4] = {{-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}, {-1, -1, -1, -1}};

// Modified drawTokens function to use the dynamic token positions and add outlines
void drawTokens(SDL_Renderer *renderer, int numPlayers, int diceRoll, int currentPlayer) {
    SDL_Color playerColors[4] = {
        {150, 0, 0, 255},    // Red
        {150, 150, 0, 255},  // Yellow
        {0, 0, 150, 255},    // Blue
        {0, 150, 0, 255}     // Green
    };

    SDL_Color highlightColor = {0, 0, 0, 255}; // Bright yellow for highlighting

    for (int i = 0; i < numPlayers; i++) {
        for (int j = 0; j < 4; j++) {
            Token *token = &tokens[i][j];
            SDL_Color color = playerColors[i];

            // Check if the token is playable
            int isPlayable = 0;
            if (i == currentPlayer) {
                int currentPos = tokenPositions[i][j];

                if (token->isHome && diceRoll == 6) {
                    isPlayable = 1; // Token can be freed
                } else if (currentPos >= 0 && currentPos + diceRoll < 56) {
                    isPlayable = 1; // Token can move within bounds
                }
            }

            // Draw highlight if playable
            if (isPlayable) {
                SDL_SetRenderDrawColor(renderer, highlightColor.r, highlightColor.g, highlightColor.b, highlightColor.a);
                for (int w = 0; w < (TOKEN_RADIUS + 6) * 2; w++) {
                    for (int h = 0; h < (TOKEN_RADIUS + 6) * 2; h++) {
                        int dx = (TOKEN_RADIUS + 6) - w;
                        int dy = (TOKEN_RADIUS + 6) - h;
                        if (dx * dx + dy * dy <= (TOKEN_RADIUS + 6) * (TOKEN_RADIUS + 6) &&
                            dx * dx + dy * dy > (TOKEN_RADIUS + 4) * (TOKEN_RADIUS + 4)) {
                            SDL_RenderDrawPoint(renderer, token->x + dx, token->y + dy);
                        }
                    }
                }
            }

            // Draw the black outline
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            for (int w = 0; w < (TOKEN_RADIUS + 2) * 2; w++) {
                for (int h = 0; h < (TOKEN_RADIUS + 2) * 2; h++) {
                    int dx = (TOKEN_RADIUS + 2) - w;
                    int dy = (TOKEN_RADIUS + 2) - h;
                    if (dx * dx + dy * dy <= (TOKEN_RADIUS + 2) * (TOKEN_RADIUS + 2)) {
                        SDL_RenderDrawPoint(renderer, token->x + dx, token->y + dy);
                    }
                }
            }

            // Draw the token circle
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            for (int w = 0; w < TOKEN_RADIUS * 2; w++) {
                for (int h = 0; h < TOKEN_RADIUS * 2; h++) {
                    int dx = TOKEN_RADIUS - w;
                    int dy = TOKEN_RADIUS - h;
                    if (dx * dx + dy * dy <= TOKEN_RADIUS * TOKEN_RADIUS) {
                        SDL_RenderDrawPoint(renderer, token->x + dx, token->y + dy);
                    }
                }
            }
        }
    }
}
