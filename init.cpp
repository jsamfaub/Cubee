#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "init.h"
#include <iostream>
#include "entity.h"
#include "window.h"
using namespace std;

extern SDL_Renderer* renderer;
extern window windows[3];
extern int screenwidth;
extern int screenheight;

bool init(void){
	bool success=1;
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) <0 ){
		cout<<"Error1"<<endl;
		success=0;
	}else{
		int imgFlags= IMG_INIT_PNG;
		if(!(IMG_Init(imgFlags) & imgFlags)){
			cout<<"Error2"<<endl;
			success=0;
		}else{
			if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0){
				cout<<"Error3"<<endl;
				success=0;
			}else{
				if(!windows[0].init()){
					success=false;
				}else{
					renderer=windows[0].getRenderer();
				}
			}
		}
	}
	return success;
}
