#ifndef _GAME_H
#define _GAME_H

#include "RenderWindow.h"
#include "bird.h"
#include "entity.h"

using namespace std;


static SDL_Texture *backgr;
static SDL_Texture *plane;
static SDL_Texture *menu;
static SDL_Texture *sound_button;
static SDL_Texture *nosound_button;
static SDL_Texture *quit_button;
static SDL_Texture *replay_button;
static SDL_Texture *bullet;
static SDL_Texture *petrol_tank;
static SDL_Texture *start_button;
static SDL_Texture *score_tex;

static Mix_Music *bckgrSound;
static Mix_Chunk *clickSound;
static Mix_Chunk *dieSound;
static Mix_Chunk *scoreSound;
static Mix_Chunk *explorationSound;

static int ScrollingBackgroundOffset = 0;
static const int ScrollingBackgroundSpeed = 1;

class Game{
public:

	Game();
	~Game();

	void Menu();
	
	void Sound();

	void afterLose();

	int getAction();

	void display();

	void loop();

	void start();

	void end();

	void Update();

	bool notLose();

};

#endif
