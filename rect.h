#pragma once
#include <SDL2/SDL.h>
#include "block.h"
class rect{
public:
	void setupTexture();
	float x;
	float y;
	float w;
	float h;
	void setCol(Uint8 r,Uint8 g,Uint8 b, Uint8 a = 0xFF);
	SDL_Color col;
	void fill(void);
	bool filled=false;
	void render(int cx,int cy,int cw,int ch);
	bool textured=false;
	blockTexture block;
};
