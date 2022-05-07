#include "entity.h"
#include "init.h"
#include "level.h"
#include "window.h"
#include <iostream>
#include <vector>
#include "sounds.h"
#include "arguments.h"
using namespace std;
SDL_Renderer* renderer=NULL;
int  screenwidth=1280;
int screenheight=720;
int tileSize=50;
string levelPath="data/levels/level1.lvl";
sound jumpSound,bumpSound,victory;
level* currentLevel=NULL;
vector<player*> players;
vector<rect*> playerRectangles;
vector<rect*> itemRectangles;
int numOfPlayers=1;//1 or 2
int numOfStars=0;
extern window windows[3];
extern controls playerControls[];

int main(int argc,char *argv[])
{
	bool over=0;
	bool win=0;
	if(!init()){
	}else{
		if(argc>1){
			handleArguments(argc,argv);
		}
		jumpSound.loadSound("data/sounds/smb3_jump.wav");
		bumpSound.loadSound("data/sounds/smb3_bump.wav");
		victory.loadSound("data/sounds/smb_stage_clear.wav");
		currentLevel=new level(levelPath.c_str());
		currentLevel->loadData();
		for(int j=0;j<currentLevel->enemies.size();j++)
			currentLevel->enemies[j]->ownType=ENEMY;
		getPlayers(players,numOfPlayers);
		//players[0]->setTexture("data/graphics/entities/player/player1.png");
		//players[1]->setTexture("data/graphics/entities/player/player2.png");
		for(int i=0;i<numOfPlayers;i++){

			players[i]->setKeycodes(playerControls[i].left,playerControls[i].right,playerControls[i].attack,playerControls[i].jump);
			players[i]->setShape(100+(i*50),100,tileSize,tileSize);
		}
		createPlayerRectangles(playerRectangles,players);
		createItemRectangles(itemRectangles,currentLevel->items);

		SDL_Event e;
		while(!over){
			while(SDL_PollEvent(&e)>0){
				if(e.type==SDL_QUIT){
					over=1;
				}
				if(e.type==SDL_KEYDOWN){
					switch(e.key.keysym.sym){
						case SDLK_q: over=1;break;
					}
				}
				for(int i=0;i<numOfPlayers;i++){
					players[i]->handleInput(e);
				}
			}
			int numOfEnemies=currentLevel->enemies.size();
			for(int i=0;i<numOfPlayers;i++){
				players[i]->move(currentLevel->w,currentLevel->h,currentLevel->blocks,currentLevel->enemyRectangles,playerRectangles,-1,i);
				playerRectangles[i]->x=players[i]->shape.x;
				playerRectangles[i]->y=players[i]->shape.y;
				playerRectangles[i]->w=players[i]->shape.w;
				playerRectangles[i]->h=players[i]->shape.h;
				players[i]->setCamera(currentLevel->w,currentLevel->h);
				if(players[i]->attacked){
					for(int j=0;j<numOfEnemies;j++){
						if(currentLevel->enemies[j]->isCollided(&players[i]->getAttackRect())){
							currentLevel->enemies[j]->getHurt();
						}
					}
					for(int j=0;j<numOfPlayers;j++){
						if(j==i)continue;
						if(players[j]->isCollided(&players[i]->getAttackRect())){
							players[j]->getHurt();
						}
					}
				}
			}
			for(int j=0;j<numOfEnemies;j++){
				for(int i=0;i<numOfPlayers;i++){if(currentLevel->enemies[j]->near(players[i]->shape,3*tileSize,3*tileSize))currentLevel->enemies[j]->follow(players[i]->shape);}
				currentLevel->enemies[j]->move(currentLevel->w,currentLevel->h,currentLevel->blocks,currentLevel->enemyRectangles,playerRectangles,j,-1);
				currentLevel->enemyRectangles[j]->x=currentLevel->enemies[j]->shape.x;
				currentLevel->enemyRectangles[j]->y=currentLevel->enemies[j]->shape.y;
				currentLevel->enemyRectangles[j]->w=currentLevel->enemies[j]->shape.w;
				currentLevel->enemyRectangles[j]->h=currentLevel->enemies[j]->shape.h;
			}
			if(!windows[0].isMinimized()){
				SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF);
				SDL_RenderClear(renderer);
				for(int i=0;i<numOfPlayers;i++){
					players[i]->setViewport();
					currentLevel->renderBG({players[i]->camera.x/4,players[i]->camera.y/4,players[i]->camera.w,players[i]->camera.h});
					int size=currentLevel->items.size();
					for(int j=0;j<size;j++){
						if(!currentLevel->items[j]->collected){
							if(players[i]->isCollided(&currentLevel->items[j]->getRect())){
								currentLevel->items[j]->interact();
							}
							currentLevel->items[j]->render(players[i]->camera);
						}
					}
					for(int j=0;j<size;j++){
						if(currentLevel->items[j]->collected&&currentLevel->items[j]->itemType==STAR){
							win=true;
						}else{
							win=false;
							break;
						}
					}
					for(int j=0;j<currentLevel->getNumOfBlocks();j++){
						currentLevel->blocks[j]->render((int)players[i]->camera.x,(int)players[i]->camera.y,(int)players[i]->camera.w,(int)players[i]->camera.h); }
					size=currentLevel->enemies.size();
					for(int j=0;j<size;j++){
						currentLevel->enemies[j]->render(players[i]->camera);
					}
					for(int j=0;j<numOfPlayers;j++){
						players[j]->render(players[i]->camera);
					}
				}
			}

			SDL_RenderPresent(renderer);
			if(win){over=true;}
		}
	}
	destroyGame();
	if(win){
		victory.play();
		cout<<"You Win!"<<endl;
		cin.get();
	}

	return 0;
}
