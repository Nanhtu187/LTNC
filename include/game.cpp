#include "game.h"

using namespace std;

static SDL_Texture *backgr;
static SDL_Texture *plane;
static SDL_Texture *menu;
static SDL_Texture *instruction_button;
static SDL_Texture *sound_button;
static SDL_Texture *quit_button;
static SDL_Texture *replay_button;
static SDL_Texture *bullet;
static SDL_Texture *petrol_tank;
static SDL_Texture *start_button;

const int WINDOW_WIDTH = 1080, WINDOW_HEIGHT = 720;

Bird bird(200, 300, 70);
RenderWindow window("test", WINDOW_WIDTH, WINDOW_HEIGHT);
vector<Entity> entity;
int score = -1;
int best_score = -1;
SDL_Event e;

string to_String(int x){
	if(!x) return "0";
	string res = "";
	while(x){
		res += (char)(x % 10 + '0');
		x /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}



Game::Game(){
	backgr = window.loadTexture("res/art/tex_bckgnd.png");
	plane = window.loadTexture("res/art/plane.png");
	//menu = window.loadTexture("res/art/tex_menu.png");
	bullet = window.loadTexture("res/art/bullet.png");
	petrol_tank = window.loadTexture("res/art/petroltank.png");
	start_button = window.loadTexture("res/art/start.png");
	instruction_button = window.loadTexture("res/art/instruction.png");
	sound_button = window.loadTexture("res/art/sound.png");
	replay_button = window.loadTexture("res/art/replay.png");
}

Game::~Game(){
	SDL_DestroyTexture(backgr);
	SDL_DestroyTexture(plane);
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(bullet);
	SDL_DestroyTexture(petrol_tank);
	SDL_DestroyTexture(start_button);
}

void Game::Sound(){

}

void Game::instruction(){
	
}

void Game::display(){
	window.render(backgr);
	window.render(plane, bird.rect);
	for(auto x: entity){
		if(x.type == 1){
			window.render(bullet, x.rect);
		}
		else {
			window.render(petrol_tank, x.rect);
		}
	}
	window.display();
}

int Game::getAction(){
	while(SDL_PollEvent(&e));
	int x, y;
	bool quit = false;
	while(quit == false)
	{
   	 	while(SDL_PollEvent(&e) != 0)
    	{
    		if(e.type == SDL_QUIT) return 0;
        	if(e.type == SDL_MOUSEBUTTONDOWN)
        	{		
         	   SDL_GetMouseState(&x,&y);
         	   cout << x << ' ' << y << '\n';
        	}
        	else continue;
        	if(200 <= x && 400 >= x && 200 <= y && 300 >= y){
        		return 1;
        	}
        	if(700 <= x && 900 >= x && 200 <= y && 300 >= y){
        		return 2;
        	}
    	}
	}	
}

int Game::waitEvent(){
	while(SDL_PollEvent(&e));
	while(1){
		if(!SDL_PollEvent(&e)) {
			continue;
		}
		switch (e.type){
			case SDL_QUIT:{
				return 0;
			}
			case SDL_MOUSEBUTTONDOWN:{
				return 1;
			}
		}
	}
	//return 0;
}

void Game::Menu(){
	window.render(backgr);
	window.render(start_button, {200, 200, 200, 100});
	window.render(instruction_button, {700, 200, 200, 100});
	window.display();
	int quit = false;
	while(!quit){
		int sign = getAction();
		if(sign == 0){
			end();
			quit = 1;
		}
		else if(sign == 1){
			start();
			quit = 1;
		}
		else if(sign == 2){
			instruction();
			quit = 1;
		}
		else if(sign == 3){
			Sound();
		}
	}
}

void Game::start(){
	bird.reset(200, 300, 50);
	entity.clear();
	score = 0;
	loop();

}

bool intersect(SDL_Rect a, SDL_Rect b){
	int x1 = a.x, x2 = b.x, y1 = a.y, y2 = b.y, w1 = a.w, w2 = b.w, h1 = a.h, h2 = b.h;
	return ((x1+w1 >= x2) && (x2+w2 >= x1) && (y1+h1 >= y2) && (y2+h2 >= y1));

}

void Game::Update(){
	SDL_Delay(50);
	if(SDL_PollEvent(&e) && e.type == SDL_MOUSEBUTTONDOWN){
		bird.dist = -10;
	}
	else {
		bird.dist += 2;
	}

	for(auto x = entity.begin(); x!= entity.end();){
		((*x).rect).x -= (*x).dist;
		if(intersect(bird.rect, (*x).rect)){
			if((*x).type == 0){
				entity.erase(x);
				++ score;
			}
		}
		++ x;
	}
	if(!entity.size()){
		Entity x;
		entity.push_back(x);
	}
	else {
		auto x = entity[0];
		if(x.rect.x <= 50) entity.erase(entity.begin());
		x = entity[entity.size() - 1];
		if(x.rect.x < WINDOW_WIDTH -  100){
			Entity x;
			entity.push_back(x);
		}
	}
}

void Game::loop(){
	int quit = 0;
	while(!quit){
		bird.move();
		display();
		Update();
		if(!notLose()) quit = 1;
	}
	afterLose();
}

void Game::afterLose(){
	best_score = max(best_score, score);
	window.render("Score:" + to_String(score), 600, 400, {255 , 255, 255});
	window.render("Best score:" + to_String(best_score), 600, 600, {255 , 255, 255});
	window.display();
	int sign = getAction();
	if(sign == 3) {
		start();
		return;
	}
	else {
		end();
		return;
	}
}

void Game::end(){
	window.quit();
}

bool Game::notLose(){
	bool ok = 1;
	for(auto x: entity){
		if(intersect(bird.rect, x.rect)){
			if(x.type == 1){
				ok = 0;
			}
		}
	}
	return ok && bird.inside(WINDOW_WIDTH, WINDOW_HEIGHT);
}