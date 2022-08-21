#include "../inc/header.h"

SDL_Texture *load_sprite(char *file_path, SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load(file_path);
    if (!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        return NULL;
    }
    SDL_Texture *sprite = SDL_CreateTextureFromSurface(renderer, surface);
    if (!sprite)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        return NULL;
    }
    SDL_FreeSurface(surface);

    // Возвращает загруженную текстуру
    return sprite; 
}

