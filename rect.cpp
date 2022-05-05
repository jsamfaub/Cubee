#include "rect.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "tileset.h"
using namespace std;

extern SDL_Renderer *renderer;
void rect::setCol(Uint8 r,Uint8 g,Uint8 b, Uint8 a){
	col={r,g,b,a};
}
void rect::fill(void){
	block.tileSheetPos={STONE.x,STONE.y,STONE.w,STONE.h};
	filled=true;
}
void rect::render(int cx,int cy,int cw,int ch){
	SDL_Rect rec={(int)x-cx,(int)y-cy,(int)w,(int)h};
	if(!textured){
	SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a);
	SDL_RenderFillRect(renderer,&rec);
	}else{
		if(tileTexture==NULL)cout<<"texture"<<endl;
		SDL_RenderCopyEx(renderer,tileTexture,&block.tileSheetPos,&rec,0.0,NULL,SDL_FLIP_NONE);
	}
}
