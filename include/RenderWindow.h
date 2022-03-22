#ifndef _RENDERWINDOW_H
#define _RENDERWINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>

using namespace std;

class RenderWindow{
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
public:
	RenderWindow(string title, int W, int H);
	RenderWindow();
	SDL_Texture* loadTexture(string path);
	void quit();
	void clear();	
	void display();
	void render(SDL_Texture* tex);
	void render(SDL_Texture* tex, SDL_Rect rect);
};

#endif