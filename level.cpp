#include "entity.h"
#include "level.h"
#include <iostream>
#include <fstream>
#include "tileset.h"
#include "sprites.h"
using namespace std;
enum TYPE { day, night, space, underground };
extern int tileSize;
extern SDL_Renderer* renderer;
struct entityInfo{
	float x;
	float y;
	float w;
	float h;
	char type;
};
vector<entityInfo> entitiesInfo;

level::level(string path){
	int type=day;
	switch(type){
		case 	     day:
		case 	   night:
		case 	   space:
		case underground: cout<<"Good type"<<endl; id=type; break;
			 default: cout<<"Bad type; setting to 0 (day)"<<endl; id=0; break;
	}
	fstream file;
	file.open(path, ios::in);
	char block=NULL;
	char ch;
	int x=0,y=0;
	bool xed=false; while(!file.eof()){ file>>ch; if(ch=='n'){y++;xed=true;}else if(!xed) x++;
	}++y;
	w=x*tileSize;
	h=y*tileSize;
	file.clear(); file.seekg(0);
	int posx=0,posy=0,index=0;

	file>>ch;
	while(!file.eof()){
		if(posx%x==0&&posx!=0) { posx=0;posy++;}
		if(ch=='n'){file>>ch;continue;}
		else{
			bool colorSet=false;
			SDL_Color c={0x00,0x00,0x00,0x00};
			switch(ch){
				case 'e':
					enemies.push_back(new enemy);
					index=enemies.size()-1;
					enemies[index]->setBasicValues((float)posx*tileSize,(float)posy*tileSize,(float)tileSize,(float)tileSize,'e');
					enemyRectangles.push_back(new rect);
					enemyRectangles[index]->x=(float)posx*tileSize;
					enemyRectangles[index]->y=(float)posy*tileSize;
					enemyRectangles[index]->w=(float)tileSize;
					enemyRectangles[index]->h=(float)tileSize;
					enemies[index]->id=index;
					break;
				case 'i':
					items.push_back(new item);
					items[items.size()-1]->setBasicValues((float)posx*tileSize,(float)posy*tileSize,(float)tileSize,(float)tileSize,'i');
					break;
				case 'r':
				case 'l':
				case 'w':
					if(!colorSet){colorSet=true;c={0xFF,0x00,0x00};}
				case 'g':
					if(!colorSet){colorSet=true;c={0x00,0xFF,0x00};}
				case 'b':
					if(!colorSet){colorSet=true;c={0x00,0x00,0xFF};}
				case 'y':
					if(!colorSet){colorSet=true;c={0xFF,0xFF,0x00};}
				case '#':
					if(!colorSet){colorSet=true;c={0xDD,0xDD,0xDD};}

					blocks.push_back(new rect);
					blocks[blocks.size()-1]->setCol(c.r,c.g,c.b);
					blocks[blocks.size()-1]->w=tileSize;
					blocks[blocks.size()-1]->h=tileSize;
					blocks[blocks.size()-1]->x=posx*tileSize;
					blocks[blocks.size()-1]->y=posy*tileSize;
					blocks[blocks.size()-1]->fill();
					if(ch=='#'||ch=='g'||ch=='r'||ch=='l'||ch=='w'){
						blocks[blocks.size()-1]->textured=true;

					}
					switch(ch){
						case '#':blocks[blocks.size()-1]->block.tileSheetPos=STONE;break;
						case 'g':blocks[blocks.size()-1]->block.tileSheetPos=GRASS;break;
						case 'r':blocks[blocks.size()-1]->block.tileSheetPos=DIRT;break;
						case 'w':blocks[blocks.size()-1]->block.tileSheetPos=WOOD;break;
						case 'l':blocks[blocks.size()-1]->block.tileSheetPos=LEAVES;break;
					}
					break;
				case '0':
				default:;
			}
			posx++;
		}
		file>>ch;
	}
	file.close();
	bg=NULL;
	levelMusic=NULL;

	playMusic();
	tileTexture=SDL_CreateTextureFromSurface(renderer,IMG_Load(TILEPATH));
	playersTexture=SDL_CreateTextureFromSurface(renderer,IMG_Load(PLAYERSPATH));
}
int level::getNumOfBlocks(){
	return blocks.size();
}
bool level::loadData(){
	loadBGTexture();
	loadMusic();
	loadEntities();
	playMusic();
	return true;
}
bool level::loadEntities(){
	int size=enemies.size();
	for(int i=0;i<size;i++){
		enemies[i]->setTexture("data/graphics/entities/enemies/red.png");
	}
}
bool level::loadBGTexture(){
	bool success=true;
	SDL_Surface* surface;
	surface=IMG_Load("data/graphics/backgrounds/test003.png");
	if(surface==NULL){
		cout<<"Error in creating background surface: "<<"data/graphics/backgrounds/test003.png"<<endl;
		success=false;
	}else{
		bg=SDL_CreateTextureFromSurface(renderer,surface);
		if(bg==NULL){
			success=false;
		}else{
			cout<<"success"<<endl;
		}
		SDL_FreeSurface(surface);
	}
	return success;
}
bool level::loadMusic(){
	bool success=true;
	levelMusic=Mix_LoadMUS("data/music/_levelmusic.mp3");
	if(levelMusic==NULL){
		cout<<Mix_GetError()<<endl;
		success=false;
	}
	return success;
}
void level::playMusic(){
	Mix_PlayMusic(levelMusic,-1);
}
void level::renderBG(rect camera){
	SDL_Rect cam={(int)camera.x,(int)camera.y,(int)camera.w,(int)camera.h};
	bgDest.w=cam.w;
	bgDest.h=cam.h;

	while(cam.x>bgDest.w)
		cam.x-=bgDest.w;
	while(cam.y>bgDest.h)
		cam.y-=bgDest.h;

	bgDest.x=-cam.x;
	bgDest.y=-cam.y;
	SDL_RenderCopy(renderer,bg,NULL,&bgDest);
	bgDest.x+=bgDest.w;
	SDL_RenderCopy(renderer,bg,NULL,&bgDest);
	bgDest.y+=bgDest.h;
	SDL_RenderCopy(renderer,bg,NULL,&bgDest);
	bgDest.x-=bgDest.w;
	SDL_RenderCopy(renderer,bg,NULL,&bgDest);
}
