#include "game.h"

using namespace std;

static SDL_Texture *backgr;
static SDL_Texture *flap;
static SDL_Texture *menu;
static SDL_Texture *bullet;
static SDL_Texture *petrol_tank;

Bird bird(200, 300, 50);
RenderWindow window("test", 1000, 800);
vector<Entity> entity;
int gas;
double LAST = 0;

Game::Game(){
	backgr = window.loadTexture("res/art/tex_bckgnd.png");
	flap = window.loadTexture("res/art/plane.png");
	menu = window.loadTexture("res/art/tex_menu.png");
	bullet = window.loadTexture("res/art/bullet.png");
	petrol_tank = window.loadTexture("res/art/petroltank.png");

}

void Game::display(){
	window.render(backgr);
	window.render(flap, bird.rect);
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

void Game::start(){
	bird.reset(200, 300, 50);
	entity.clear();
	window.render(menu);
	window.display();
	gas = 1000;
	SDL_Event e;
	while(SDL_PollEvent(&e));
	int quit = 0;
	while(!quit){
		if(!SDL_PollEvent(&e)) {
			continue;
		}
		switch (e.type){
			case SDL_QUIT:{
				quit = 1;
				end();
				break;
			}
			case SDL_MOUSEBUTTONDOWN:{
				quit = 1;
				loop();
				break;
			}
		}
	}

}

bool intersect(SDL_Rect a, SDL_Rect b){
	int x1 = a.x, x2 = b.x, y1 = a.y, y2 = b.y, w1 = a.w, w2 = b.w, h1 = a.h, h2 = b.h;
	return ((x1+w1 >= x2) && (x2+w2 >= x1) && (y1+w1 >= y2) && (y2+w2 >= y1));

}

void Game::Update(){
	SDL_Event e;
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
				gas = min(1000, gas + 200);
				entity.erase(x);
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
		if(x.rect.x < 900){
			Entity x;
			entity.push_back(x);
		}
	}
	-- gas;
}

void Game::loop(){
	int quit = 0;
	while(!quit){
		bird.move();
		display();
		Update();
		if(!notLose()) quit = 1;
		cout << gas << '\n';
	}
	cout << 1.0 * clock()/CLOCKS_PER_SEC - LAST;
	LAST = clock()/CLOCKS_PER_SEC;
	start();
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
	return gas && ok && bird.inside(1000, 800);
}