#pragma once

#ifndef ENDGAME_H
#define ENDGAME_H

// SDL2 Frameworks
#include <SDL2/SDL.h>
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define SPEED 300


void menu_call(SDL_Window *window, SDL_Renderer *renderer, int lives);
void level1_call(SDL_Window *window, SDL_Renderer *renderer, int lives);
void level2_call(SDL_Window *window, SDL_Renderer *renderer, int lives);
SDL_Texture *load_sprite(char *file_path, SDL_Renderer *renderer);
bool check_color(SDL_Surface *surface, int x, int y, Uint8 red_forbid, Uint8 green_forbid, Uint8 blue_forbid);


#endif
