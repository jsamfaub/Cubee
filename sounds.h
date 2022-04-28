#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
using namespace std;
class sound{
public:
	void loadSound(string);
	Mix_Chunk *sfx=NULL;
	void play();
	int channel=-1;
};
