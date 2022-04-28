#pragma once
#include "entity.h"
using namespace std;
class level
{
public:
	level(string path);
	~level();

	int id=0;
	bool loadBGTexture(); SDL_Texture* bg;
	void renderBG(rect camera);
	bool loadMusic(); Mix_Music* levelMusic;
	bool loadData();
	bool loadEntities();
	void playMusic();
	
	void renderBlocks(rect &camera);

	vector<rect*> getBlocks();
	int blockNum;
	int getNumOfBlocks();
	int w,h;

	vector<rect*> blocks;
	vector<enemy*> enemies;
	vector<rect*> enemyRectangles;
	vector<item*> items;

	SDL_Rect bgDest={0,0,0,0};
};
