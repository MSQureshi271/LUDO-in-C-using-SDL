#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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