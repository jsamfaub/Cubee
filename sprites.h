#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
const SDL_Rect ONE ={0,0,16,16};
const SDL_Rect TWO ={0,16,16,16};
const SDL_Rect THREE ={0,32,16,16};
const SDL_Rect FOUR ={0,48,16,16};
extern SDL_Texture* playersTexture;
#define PLAYERSPATH "data/graphics/entities/player/players.png"
