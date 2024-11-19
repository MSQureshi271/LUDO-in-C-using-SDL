#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)
#define DICE_SIZE 100
#define DOT_SIZE 15
#define TOKEN_RADIUS (CELL_SIZE / 3)
#define OUTLINE_RADIUS (TOKEN_RADIUS+2)

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

void displayWinner(SDL_Renderer *renderer, int winner, TTF_Font *font) {
    char winnerText[50];
    sprintf(winnerText, "Player %d Wins!", winner + 1); // Format the winner's message

    // Define player colors
    SDL_Color playerColors[4] = {
        {255, 0, 0, 255},    // Red
        {255, 255, 0, 255},  // Yellow
        {0, 0, 255, 255},    // Blue
        {0, 255, 0, 255}     // Green
    };

    SDL_Color textColor = playerColors[winner]; // Use the winner's color
    SDL_Rect textRect = {SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100};

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Render the winner text
    renderText(renderer, winnerText, textRect, textColor, font);

    SDL_RenderPresent(renderer);

    // Pause to let the winner announcement stay visible
    SDL_Delay(5000); // Wait for 5 seconds
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


// Function to draw the Ludo board
void drawLudoBoard(SDL_Renderer *renderer) {
    // Colors for the players' zones and home rows
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color green = {0, 255, 0, 255};
    SDL_Color blue = {0, 0, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};
    SDL_Color redHome = {255, 150, 150, 255};    // Lighter color for home row
    SDL_Color greenHome = {150, 255, 150, 255};
    SDL_Color blueHome = {150, 150, 255, 255};
    SDL_Color yellowHome = {255, 255, 150, 255};

    // Draw the grid and player zones
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            SDL_Rect cell = {col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE};

            // Draw white border around every cell
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &cell);

            // Home row coloring (pathway) with white borders for individual cells
            if (row >= 6 && row <= 8) {
                switch(row){
                    case 6:
                        if(col == 1){
                            SDL_SetRenderDrawColor(renderer, redHome.r, redHome.g, redHome.b, redHome.a);
                            SDL_RenderFillRect(renderer, &cell);
                            // Draw black border around the cell
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Changed to black
                            SDL_RenderDrawRect(renderer, &cell); 
                        }
                        else if(col == 12){
                            SDL_SetRenderDrawColor(renderer, yellowHome.r, yellowHome.g, yellowHome.b, yellowHome.a);
                            SDL_RenderFillRect(renderer, &cell);
                            // Draw black border around the cell
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Changed to black
                            SDL_RenderDrawRect(renderer, &cell);
                        }
                        break;
                    case 7:                       
                        // Home row for Red (Row 7, from 0 to 5 in column range)
                        if (col > 0 && col < 6) {
                            SDL_SetRenderDrawColor(renderer, redHome.r, redHome.g, redHome.b, redHome.a);
                            SDL_RenderFillRect(renderer, &cell);
                            // Draw black border around the cell
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Changed to black
                            SDL_RenderDrawRect(renderer, &cell);
                        }
                        // Home row for Green (Row 7, from 9 to 14 in column range)
                        else if (col >= 9 && col <= 13) {
                            SDL_SetRenderDrawColor(renderer, yellowHome.r, yellowHome.g, yellowHome.b, yellowHome.a);
                            SDL_RenderFillRect(renderer, &cell);
                            // Draw black border around the cell
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Changed to black
                            SDL_RenderDrawRect(renderer, &cell);
                        }
                        break;
                    case 8:
                        if(col == 2){
                            SDL_SetRenderDrawColor(renderer, redHome.r, redHome.g, redHome.b, redHome.a);
                            SDL_RenderFillRect(renderer, &cell);
                            // Draw black border around the cell
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Changed to black
                            SDL_RenderDrawRect(renderer, &cell);
                        }
                        else if(col == 13){
                            SDL_SetRenderDrawColor(renderer, yellowHome.r, yellowHome.g, yellowHome.b, yellowHome.a);
                            SDL_RenderFillRect(renderer, &cell);
                            // Draw black border around the cell
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Changed to black
                            SDL_RenderDrawRect(renderer, &cell);
                        }
                        break;
                }
            }
            if (col >= 6 && col <= 8) {
                switch(col){
                    case 6:
                        if(row == 2){
                            SDL_SetRenderDrawColor(renderer, greenHome.r, greenHome.g, greenHome.b, greenHome.a);
                            SDL_RenderFillRect(renderer, &cell);
                            // Draw black border around the cell
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Changed to black
                            SDL_RenderDrawRect(renderer, &cell);                            
                        }
                        else if(row == 13){
                            SDL_SetRenderDrawColor(renderer, blueHome.r, blueHome.g, blueHome.b, blueHome.a);
                            SDL_RenderFillRect(renderer, &cell);
                            // Draw black border around the cell
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Changed to black
                            SDL_RenderDrawRect(renderer, &cell);                            
                        }
                        break;
                    case 7:
                        // Home row for Blue (Column 7, from 0 to 5 in row range)
                        if (row > 0 && row < 6) {
                            SDL_SetRenderDrawColor(renderer, greenHome.r, greenHome.g, greenHome.b, greenHome.a);
                            SDL_RenderFillRect(renderer, &cell);
                            // Draw black border around the cell
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Changed to black
                            SDL_RenderDrawRect(renderer, &cell); 
                        }
                        // Home row for Yellow (Column 7, from 9 to 14 in row range)
                        else if (row >= 9 && row <= 13) {
                            SDL_SetRenderDrawColor(renderer, blueHome.r, blueHome.g, blueHome.b, blueHome.a);
                            SDL_RenderFillRect(renderer, &cell);
                            // Draw black border around the cell
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Changed to black
                            SDL_RenderDrawRect(renderer, &cell);    
                        }
                        break;
                    case 8:
                        if(row == 1){
                            SDL_SetRenderDrawColor(renderer, greenHome.r, greenHome.g, greenHome.b, greenHome.a);
                            SDL_RenderFillRect(renderer, &cell);
                            // Draw black border around the cell
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Changed to black
                            SDL_RenderDrawRect(renderer, &cell); 
                        }
                        else if(row == 12){
                            SDL_SetRenderDrawColor(renderer, blueHome.r, blueHome.g, blueHome.b, blueHome.a);
                            SDL_RenderFillRect(renderer, &cell);
                            // Draw black border around the cell
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Changed to black
                            SDL_RenderDrawRect(renderer, &cell); 
                        }
                        break;
                }
            }

            // Player zones coloring
            if (row < 6 && col < 6) {
                SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a);
                SDL_RenderFillRect(renderer, &cell);
            } else if (row < 6 && col >= 9) {
                SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, green.a);
                SDL_RenderFillRect(renderer, &cell);
            } else if (row >= 9 && col < 6) {
                SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a);
                SDL_RenderFillRect(renderer, &cell);
            } else if (row >= 9 && col >= 9) {
                SDL_SetRenderDrawColor(renderer, yellow.r, yellow.g, yellow.b, yellow.a);
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }

    // Draw the central area
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect centralArea = {6 * CELL_SIZE, 6 * CELL_SIZE, 3 * CELL_SIZE, 3 * CELL_SIZE};
    SDL_RenderFillRect(renderer, &centralArea);

    // Draw black border around the central area
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &centralArea);
}

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

// Function to roll the dice with a shuffling effect
int rollDice(SDL_Renderer *renderer, int x, int y) {
    int finalRoll = (rand() % 6) + 1;  // Determine the final dice number
    int shuffleRoll;                    // Variable to hold intermediate random rolls
    Uint32 startTime = SDL_GetTicks();  // Get the current time

    // Loop to display random numbers for 1 second
    while (SDL_GetTicks() - startTime < 1000) {  // Shuffle for 1 second
        shuffleRoll = (rand() % 6) + 1;  // Get a random number for shuffling

        // Draw the shuffled dice number in the designated area
        drawDice(renderer, shuffleRoll, x, y);  // Display shuffled dice number
        SDL_RenderPresent(renderer);
        
        SDL_Delay(100);  // Delay for 100ms to create a shuffling effect
    }

    // Draw the final rolled number
    drawDice(renderer, finalRoll, x, y);
    SDL_RenderPresent(renderer);

    return finalRoll;
}

// Structure for tokens
typedef struct {
    int x, y;           // Current position
    int isHome;         // 1 if in home zone, 0 otherwise
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
        }
    }
}


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



// Function to move the token
void moveToken(Token *token, int diceRoll, int currentPlayer, SDL_Renderer *renderer, TTF_Font *font) {
    if (token->isHome && diceRoll == 6) {
        token->isHome = 0;
        tokenPositions[currentPlayer][token - tokens[currentPlayer]] = 0; // Set to the start of the path
        token->x = (paths[currentPlayer][0].x + 0.5) * CELL_SIZE;
        token->y = (paths[currentPlayer][0].y + 0.5) * CELL_SIZE;
    } else if (!token->isHome) {
        int *currentPos = &tokenPositions[currentPlayer][token - tokens[currentPlayer]];
        int newPos = *currentPos + diceRoll;

        if (newPos == 56) { // Exact win condition
            *currentPos = newPos;
            SDL_Point newPosPoint = paths[currentPlayer][newPos];
            token->x = (newPosPoint.x + 0.5) * CELL_SIZE;
            token->y = (newPosPoint.y + 0.5) * CELL_SIZE;

            displayWinner(renderer, currentPlayer, font); // Announce the winner
            running = 0; // Terminate the game
            return;
        } else if (newPos < 56) { // Move only if not overshooting
            *currentPos = newPos;
            SDL_Point newPosPoint = paths[currentPlayer][newPos];
            token->x = (newPosPoint.x + 0.5) * CELL_SIZE;
            token->y = (newPosPoint.y + 0.5) * CELL_SIZE;
        }
    }
}

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


// Main game loop
int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    srand(time(NULL));

    SDL_Window *window = SDL_CreateWindow("Ludo Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (window == NULL || renderer == NULL) {
        printf("Could not create window or renderer! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("Montserrat-ExtraBoldItalic.ttf", 24);
    if (!font) {
        printf("Unable to load font: %s\n", TTF_GetError());
        return -1;
    }

    int numPlayers = displayStartMenu(renderer, font);
    initializeTokens(numPlayers);

    SDL_Event event;

    // Coordinates to draw the dice in the center area
    int diceX = 7 * CELL_SIZE + (CELL_SIZE / 2) - (DICE_SIZE / 2);
    int diceY = 7 * CELL_SIZE + (CELL_SIZE / 2) - (DICE_SIZE / 2);

    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
                // Roll the dice when Enter is pressed
                if (!isDiceRolled) {
                    diceResult = rollDice(renderer, diceX, diceY);
                    isDiceRolled = 1;
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Handle token selection
                selectedToken = handleTokenSelection(&event, currentPlayer);
            }
        }

        if (isDiceRolled) {
            int anyTokenMovable = 0;

            for (int i = 0; i < 4; i++) {
                Token *token = &tokens[currentPlayer][i];
                if (!token->isHome || (token->isHome && diceResult == 6)) {
                    anyTokenMovable = 1;
                    break;
                }
            }

            if (anyTokenMovable && selectedToken != -1) {
                Token *token = &tokens[currentPlayer][selectedToken];
                moveToken(token, diceResult, currentPlayer, renderer, font);

                if (running == 0) break; // Exit if a winner is found

                selectedToken = -1;
                if (diceResult != 6) {
                    currentPlayer = (currentPlayer + 1) % numPlayers;
                }

                isDiceRolled = 0;
                diceResult = 0;
            } else if (!anyTokenMovable) {
                SDL_Delay(1000);
                currentPlayer = (currentPlayer + 1) % numPlayers;
                isDiceRolled = 0;
                diceResult = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        drawLudoBoard(renderer);
        drawTokens(renderer, numPlayers, diceResult, currentPlayer);
        drawDice(renderer, diceResult, diceX, diceY);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}