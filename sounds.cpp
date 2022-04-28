#include "sounds.h"
#include <iostream>
void sound::loadSound(string file){
	sfx=Mix_LoadWAV(file.c_str());
}
void sound::play(void){
	if(sfx==NULL){
		cout<<"This sound was unable to load"<<endl;
		return;
	}
	Mix_PlayChannel(channel,sfx,0);
}
