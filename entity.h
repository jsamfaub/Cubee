#pragma once
#include <SDL2/SDL.h>
#include "rect.h"
#include <vector>
#include "velocity.h"
#include <string>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "LTimer.h"
#include "sounds.h"
enum TYPES {BLOCK=1,ENEMY,PLAYER,ITEM};
enum ITEMTYPES {STAR};
struct controls{
	int left,right,attack,jump;
};
using namespace std;
class entity{
public:
	int id=0;
	int type=0;
	int ownType=0;
	int hp=20;
	int playerNum=0;
	//data and coordinates
	void setBasicValues(float,float,float,float,char);
	//~entity();
	bool setTexture(std::string);
	rect &setShape(float x,float y,float w,float h);
	rect shape,initialShape;
	void render(rect &camera);
	//movement
	void turnLeft();void turnRight();
	void move(int levelwidth,int levelheight,std::vector<rect*>& blocks,std::vector<rect*>& enemies,vector<rect*> &players,int enemyId,int playerId); //updates the position based on previous coordinate changes and checks collision with other objects
	rect& getCollider();
	bool isCollided(rect *ent);
	bool checkIfCollidedLeft(vector<rect*>& rects,int type);
	bool checkIfCollidedRight(vector<rect*>& rects,int type);
	bool checkIfCollidedTop(vector<rect*>& rects,int type);
	bool checkIfCollidedBottom(vector<rect*>& rects,int type);
	bool near(rect &ent,float xDistance,float yDistance);
	velocity speed;
	SDL_Texture *texture=NULL;
	SDL_RendererFlip flipped=SDL_FLIP_NONE;
	bool grounded=false;
	LTimer jumpTimer;
	LTimer attackTimer;
	bool jumped=false;
	int jumpTime=400;
	float initJumpSpeed=0;
	int fallTime=400;
	LTimer fallTimer;
	LTimer headBumpTimer;
	int headBumpTime=80;
	bool headBumped=0;
	void attack();
	void reachGround();
	bool attacked=0;
	rect &getAttackRect();
	void getHurt();
	void die();
	bool touchingX=false;
	bool touchingY=false;
	rect& getRect(void);
};
class enemy:public entity{
public:
	void follow(rect &ent);
};
class item:public entity{
public:
	sound* collectSound=NULL;
	Mix_Chunk* useSound=NULL;
	void hearCollect();
	void hearUse();
	void interact();
	int itemType=-1;
	bool collected=0;
	void collect();
	void setItemType(int);
};
class player:public entity{
public:
	void setBasicValues(float,float,float,float,int);
	rect camera;
	SDL_Rect viewport={0,0,1280,720};
	item* itemHeld=NULL;
	void setKeycodes(SDL_Keycode left,SDL_Keycode right,SDL_Keycode attack,SDL_Keycode jump);
	SDL_Keycode leftKey=-1,rightKey=-1,attackKey=-1,jumpKey=-1;
	void handleInput(SDL_Event &e);
	void jump();
	void respawn();
	void renderHealthBar();
	void setViewport();
	void renderTest();
	void setCamera(int lvlw,int lvlh);
};
void getPlayers(vector<player*> &players,int);
void createPlayerRectangles(vector<rect*> &rects,vector<player*>);
void createItemRectangles(vector<rect*> &rects,vector<item*>);
