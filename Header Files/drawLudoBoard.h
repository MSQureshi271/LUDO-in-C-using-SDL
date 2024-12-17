#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)

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
