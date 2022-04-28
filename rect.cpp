#include "rect.h"

extern SDL_Renderer *renderer;
void rect::setCol(Uint8 r,Uint8 g,Uint8 b, Uint8 a){
	col={r,g,b,a};
}
void rect::fill(void){
	filled=true;
}
void rect::render(int cx,int cy,int cw,int ch){
	SDL_Rect rec={(int)x-cx,(int)y-cy,(int)w,(int)h};
	SDL_SetRenderDrawColor(renderer,col.r,col.g,col.b,col.a);
	SDL_RenderFillRect(renderer,&rec);
}
