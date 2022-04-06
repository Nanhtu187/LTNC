#ifndef _GAME_H
#define _GAME_H

#include "RenderWindow.h"
#include "bird.h"
#include "entity.h"

using namespace std;

class Game{
public:

	Game();

	int waitEvent();

	void display();

	void loop();

	void start();

	void end();

	void Update();

	bool notLose();

};

#endif
