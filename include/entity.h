#pragma once
#include <bits/stdc++.h>
//#include "random.h"
#include <SDL2/SDL.h>


using namespace std;

class Entity{
public:
	SDL_Rect rect;
	int dist = 5;
	int type;

	Entity(SDL_Rect _rect, int _type);
	
	Entity();

	void move();

	bool inside(int w, int h);
};