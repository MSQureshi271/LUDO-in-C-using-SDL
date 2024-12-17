#include <SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define BOARD_SIZE 15
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)

int isSafeGrid(int x, int y) {
    SDL_Point safeGrids[] = {
        {1, 6}, {2, 8}, {12, 6}, {13, 8}, {6, 2}, {8, 1}, {6, 13}, {8, 12}
    };
    int numSafeGrids = sizeof(safeGrids) / sizeof(safeGrids[0]);

    for (int i = 0; i < numSafeGrids; i++) {
        if (safeGrids[i].x == x && safeGrids[i].y == y) {
            return 1; // Position is a safe grid
        }
    }
    return 0; // Not a safe grid
}