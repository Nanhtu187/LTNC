#ifndef _RENDERWINDOW_H
#define _RENDERWINDOW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>
//#include <game.h>

using namespace std;

static const int WINDOW_WIDTH = 1080, WINDOW_HEIGHT = 720;

class RenderWindow{
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	TTF_Font* font;
public:
	RenderWindow(string title, int W, int H);
	RenderWindow();
	SDL_Texture* loadTexture(string path);
	Mix_Music* loadMusic(string path);
	Mix_Chunk* loadChunk(string path);
	void quit();
	void clear();	
	void display();
	void render(SDL_Texture* tex);
	void render(SDL_Texture* tex, int posX);
	void render(SDL_Texture* tex, SDL_Rect rect);
	void render(string text, int _x, int _y, SDL_Color fg);
	void musicPlay(Mix_Music* music);
	void chunkPlay(Mix_Chunk* chunk);

};

#endif