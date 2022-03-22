#ifndef _BIRD_H
#define _BIRD_H

#include <bits/stdc++.h> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Bird {
public:
	SDL_Rect rect;
	int dist;
	Bird(int _x, int _y, int _size);

	Bird();

	void move();

	void reset(int _x, int _y, int _size);

	bool inside(int w, int h);
};

#endif