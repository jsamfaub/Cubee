#include "entity.h"
#include "sounds.h"
#include <iostream>
using namespace std;
extern SDL_Renderer *renderer;
extern int screenwidth;
extern int screenheight;
extern int tileSize;
extern sound jumpSound;extern sound bumpSound;
//entity::entity(){
//}
//entity::~entity(){
//}
void entity::setBasicValues(float x,float y,float w,float h,char type){
	shape={x,y,w,h};
	id=type;
}
void player::setBasicValues(float x,float y,float w,float h,int player){
	shape={x,y,w,h};
	playerNum=player;
}
bool entity::setTexture(string path){
	bool success=true;

	if(texture!=NULL)SDL_DestroyTexture(texture);
	SDL_Surface* surface=NULL;
	surface=IMG_Load(path.c_str());
	texture=SDL_CreateTextureFromSurface(renderer,surface);
	if(texture==NULL){
		cout<<"Couldn't load texture!"<<endl;
		success=false;
	}
	SDL_FreeSurface(surface);
	return success;
}
rect& entity::setShape(float x, float y, float w, float h){
	initialShape={x,y,w,h};
	shape={x,y,w,h};
	return shape;
}
void entity::render(rect& camera){
	SDL_Rect renderShape;
	renderShape.w=(int)shape.w;
	renderShape.h=(int)shape.h;
	renderShape.x=(int)shape.x-camera.x;
	renderShape.y=(int)shape.y-camera.y;
	SDL_RenderCopyEx(renderer,texture,NULL,&renderShape,0.0,NULL,flipped);
}
void entity::turnLeft(){
	flipped=SDL_FLIP_HORIZONTAL;
}
void entity::turnRight(){
	flipped=SDL_FLIP_NONE;
}
void entity::move(int levelwidth,int levelheight,vector<rect*>& blocks,vector<rect*>& enemies,vector<rect*>& players,int enemyId,int playerId){

	rect initial=shape;
	shape.x+=speed.x;
	//cout<<"speedx:"<<speed.x<<endl;
	int size=blocks.size();
	int enemySize=enemies.size();
	int playerSize=players.size();
	//cout<<"X:"<<shape.x<<"Y:"<<shape.y<<endl;
	
	for(int i=0;i<size;i++){
		if(isCollided(blocks[i]) && speed.x>=0){
			shape.x=blocks[i]->x-shape.w;
			break;
		}
		if(isCollided(blocks[i]) && speed.x<0){
			shape.x=blocks[i]->x+blocks[i]->w;
			break;
		}
	}
	for(int i=0;i<enemySize;i++){
		if(i==enemyId)continue;
		if(isCollided(enemies[i]) && speed.x>=0){
			shape.x=enemies[i]->x-shape.w;
			break;
		}
		if(isCollided(enemies[i]) && speed.x<0){
			shape.x=enemies[i]->x+enemies[i]->w;
			break;
		}
	}
	for(int i=0;i<playerSize;i++){
		if(i==playerId)continue;
		if(isCollided(players[i]) && speed.x>=0){
			shape.x=players[i]->x-shape.w;
			break;
		}
		if(isCollided(players[i]) && speed.x<0){
			shape.x=players[i]->x+players[i]->w;
			break;
		}
	}

	if(shape.x<0.0)shape.x=0.0;
	if(shape.x>levelwidth-shape.w)shape.x=levelwidth-shape.w-1.0;
	speed.y=10;
	int initShapey=shape.y;
	if(jumped && jumpTimer.isStarted()){
		if(jumpTimer.getTicks()>=jumpTime){
			jumpTimer.stop();
			jumped=0;
		}else{
			shape.y-= (float)((int) (speed.jump * (jumpTime/100)-((float)jumpTimer.getTicks()/100)*((float)jumpTimer.getTicks()/100)));
		}
	}else{
		if(headBumped){
			if(headBumpTimer.getTicks()>=headBumpTime){
				headBumped=0;
				headBumpTimer.stop();
			}
		}else
			shape.y+=speed.y;
	}
	grounded=false;
	for(int i=0;i<size;i++){
		if(isCollided(blocks[i]) && shape.y>=initShapey){
			shape.y=blocks[i]->y-shape.h;
			grounded=true;
			jumped=false;
			break;
		}
		if(isCollided(blocks[i]) && jumped){
			shape.y=blocks[i]->y+blocks[i]->h;
			jumpTimer.stop();
			Mix_HaltChannel(-1);
			headBumpTimer.start();headBumped=1;bumpSound.play();

			break;
		}
	}
	for(int i=0;i<enemySize;i++){
		if(i==enemyId)continue;
		if(isCollided(enemies[i]) && speed.y>=0){
			shape.y=enemies[i]->y-shape.h;
			grounded=true;
			jumped=false;
			break;
		}
		if(isCollided(enemies[i]) && speed.y<0){
			shape.y=enemies[i]->y+enemies[i]->h;
			break;
		}
	}
	for(int i=0;i<playerSize;i++){
		if(i==playerId)continue;
		if(isCollided(players[i]) && speed.y>=0){
			shape.y=players[i]->y-shape.h;
			grounded=true;
			jumped=false;
			break;
		}
		if(isCollided(players[i]) && speed.y<0){
			shape.y=players[i]->y+players[i]->h;
			break;
		}
	}
	if(shape.y<0.0)shape.y=0.0;
	if(shape.y>levelheight-shape.h)shape.y=levelheight-shape.h-1.0;

	shape.y=650.0;
}
rect& entity::getCollider(){
	return shape;
}
bool entity::isCollided(rect *ent){
	if(shape.y>=ent->y+ent->h){
		return false;
	}
	if(ent->y>=shape.y+shape.h){
		return false;
	}
	if(shape.x>=ent->x+ent->w){
		return false;
	}
	if(ent->x>=shape.x+shape.w){
		return false;
	}
	return true;
}
bool entity::near(rect &ent, float xDistance, float yDistance){
	if(abs(ent.x-shape.x)<=xDistance && abs(ent.y-shape.y)<=yDistance){
		return true;
	}
	return false;
}
void item::hearCollect(){
	cout<<"Collect!"<<endl;
}
void item::hearUse(){
	cout<<"Use!"<<endl;
}
void entity::attack(){
	cout<<"Attack!"<<endl;
	cout<<"X:"<<shape.x<<endl;
	cout<<"Y:"<<shape.y<<endl;
}
void player::jump(){
	initJumpSpeed=speed.jump;
	jumpTimer.start();
	grounded=0;
	jumped=1;
	jumpSound.play();
}
void entity::die(){
	cout<<"Die!"<<endl;
}
rect& entity::getAttackRect(){
	static rect lol={-1.0,-1.0,-1.0,-1.0};
	return lol;
}
void entity::getHurt(){
	cout<<"hurt"<<endl;
}
void player::respawn(){
	cout<<"Respawned!"<<endl;
}
void player::renderHealthBar(){
	cout<<"Render health bar!"<<endl;
}
void getPlayers(vector<player*> &players,int numOfPlayers){
	switch(numOfPlayers){
		case 1:players.push_back(new player);players[0]->setBasicValues((float)tileSize,(float)tileSize,(float)tileSize,(float)tileSize,1);players[0]->camera={0,0,screenwidth,screenheight};break;
		case 2:players.push_back(new player);players[0]->setBasicValues((float)2*tileSize,(float)tileSize,(float)tileSize,(float)tileSize,1);players[0]->camera={0,0,screenwidth/2,screenheight};players[0]->viewport={0,0,screenwidth/2,screenheight};
players.push_back(new player);players[1]->setBasicValues((float)tileSize,(float)tileSize,(float)tileSize,(float)tileSize,2);players[1]->camera={0,0,screenwidth/2,screenheight};players[1]->viewport={screenwidth/2,0,screenwidth/2,screenheight};break;
		case 3:
		case 4:
		default: cout<<"Error: wrong number of players: "<<numOfPlayers<<endl;break;
	}
}
void player::setKeycodes(SDL_Keycode left, SDL_Keycode right, SDL_Keycode attack, SDL_Keycode jump){
	leftKey=left;
	rightKey=right;
	jumpKey=jump;
	attackKey=attack;
}
void player::handleInput(SDL_Event &e){
	if(e.type==SDL_KEYDOWN && e.key.repeat==0){
		if(e.key.keysym.sym==leftKey){
			speed.x=-speed.baseSpeed;
			turnLeft();
		}
		if(e.key.keysym.sym==rightKey){
			speed.x=speed.baseSpeed;
			turnRight();
		}
		if(e.key.keysym.sym==jumpKey){
			if(grounded)jump();
		}
		if(e.key.keysym.sym==attackKey){
			if(!attacked)attack();
		}
	}
	if(e.type==SDL_KEYUP && e.key.repeat==0){
		if(e.key.keysym.sym==leftKey){
			if(speed.x<0)speed.x=0;
		}
		if(e.key.keysym.sym==rightKey){
			if(speed.x>0)speed.x=0;
		}
	}
}
void player::setViewport(){
	SDL_RenderSetViewport(renderer,&viewport);
}
void player::setCamera(int levelwidth,int levelheight){
	camera.x=shape.x+(shape.w/2) - (viewport.w/2);
	camera.y=shape.y+(shape.h/2) - (viewport.h/2);
	if(camera.x<=0) camera.x=0;
	if(camera.x+camera.w>=levelwidth) camera.x=levelwidth-camera.w;

	if(camera.y<=0) camera.y=0;
	if(camera.y+camera.h>=levelheight) camera.y=levelheight-camera.h;
}
void enemy::follow(rect &ent){
	if(shape.x<ent.x){
		speed.x=speed.baseSpeed/2;
		turnRight();
	}else if(shape.x>ent.x){
		speed.x=-speed.baseSpeed/2;
		turnLeft();
	}else{
		speed.x=0;
	}
}
void createPlayerRectangles(vector<rect*> &rectangles,vector<player*> players){
	int size=players.size();
	float x,y,w,h;
	for(int i=0;i<size;i++){
		x=players[i]->shape.x;
		y=players[i]->shape.y;
		w=players[i]->shape.w;
		h=players[i]->shape.h;
		rectangles.push_back(new rect);
		rectangles[rectangles.size()-1]->x=x;
		rectangles[rectangles.size()-1]->y=y;
		rectangles[rectangles.size()-1]->w=w;
		rectangles[rectangles.size()-1]->h=h;
	}
}
