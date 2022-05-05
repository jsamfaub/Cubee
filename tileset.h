#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
const SDL_Rect GLASS ={0,0,16,16};
const SDL_Rect STONE ={(13*16)+13,(6*16)+6,16,16};
const SDL_Rect GRASS ={(2*16)+2,(6*16)+6,16,16};
const SDL_Rect DIRT  ={(2*16)+2,(7*16)+7,16,16};
const SDL_Rect LEAVES={(14*16)+14,(3*16)+3,16,16};
const SDL_Rect WOOD  ={(14*16)+14,(4*16)+4,16,16};
extern SDL_Texture* tileTexture;
#define TILEPATH "data/graphics/blocks/smw.png"
