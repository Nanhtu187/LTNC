#include "game.h"

using namespace std;

Bird bird(200, 300, 70);
RenderWindow window("test", WINDOW_WIDTH, WINDOW_HEIGHT);
vector<Entity> entity;
int score = -1;
int best_score = -1;
int isPlayingMusic = 0;
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
	backgr = window.loadTexture("res/art/tex_bckgr.png");
	plane = window.loadTexture("res/art/plane.png");
	bullet = window.loadTexture("res/art/bullet.png");
	petrol_tank = window.loadTexture("res/art/petroltank.png");
	start_button = window.loadTexture("res/art/start.png");
	sound_button = window.loadTexture("res/art/sound.png");
	nosound_button = window.loadTexture("res/art/nosound.png");
	replay_button = window.loadTexture("res/art/replay.png");
	score_tex = window.loadTexture("res/art/score.png");

	bckgrSound = window.loadMusic("res/sound/bckgrSound.mp3");
	dieSound = window.loadChunk("res/sound/explorationSound.wav");
	scoreSound = window.loadChunk("res/sound/scoreSound.wav");
	clickSound = window.loadChunk("res/sound/clickSound.wav");
	explorationSound = window.loadChunk("res/sound/explorationSound.wav");
	Sound();
}

Game::~Game(){
	SDL_DestroyTexture(backgr);
	SDL_DestroyTexture(plane);
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(bullet);
	SDL_DestroyTexture(petrol_tank);
	SDL_DestroyTexture(start_button);
	SDL_DestroyTexture(sound_button);
	SDL_DestroyTexture(replay_button);
	SDL_DestroyTexture(score_tex);
}

void Game::Sound(){
	isPlayingMusic ^= 1;
	window.musicPlay(bckgrSound);
}

void Game::display(){
	window.clear();

	window.render(backgr, WINDOW_WIDTH-ScrollingBackgroundOffset);
	window.render(backgr, 0-ScrollingBackgroundOffset);
	ScrollingBackgroundOffset += ScrollingBackgroundSpeed;
	if (ScrollingBackgroundOffset >= WINDOW_WIDTH) ScrollingBackgroundOffset = 0;

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
		SDL_Delay(10);
   	 	if(SDL_PollEvent(&e) != 0)
    	{
    		if(e.type == SDL_QUIT) return 0;
        	if(e.type == SDL_MOUSEBUTTONDOWN)
        	{		
        		window.chunkPlay(clickSound);
         	   	SDL_GetMouseState(&x,&y);
         	   	//cout << x << ' ' << y << '\n';
        	}
        	else continue;
        	if(400 <= x && 600 >= x && 200 <= y && 400 >= y){
        		return 1;
        	}
        	if(900 <= x && x <= 1000 && 600 <= y && y <= 700){
        		return 2;
        	}
        	if(450 <= x && 550 >= x && 400 <= y && 500 >= y){
        		return 3;
        	}
    	}
	}	
}


void Game::Menu(){
	window.clear();
	window.render(backgr);
	window.render(start_button, {400, 200, 200, 200});
	if(isPlayingMusic) window.render(sound_button, {900, 600, 100, 100});
	else window.render(nosound_button, {900, 600, 100, 100});
	window.display();
	int quit = false;
	while(!quit){
		int sign = getAction();
		if(sign == 0){
			end();
			quit = 1;
		}
		else if(sign == 1){
			SDL_Delay(200);
			start();
			quit = 1;

		}
		else if(sign == 2){
			Sound();
			Menu();
			quit = 1;
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
	int x1 = a.x, x2 = b.x, y1 = a.y, y2 = b.y, w1 = a.x + a.w, w2 = b.x + b.w, h1 = a.y + a.h, h2 = b.y + b.h;
	return !(x1 > w2 || x2 > w1 || y1 > h2 || y2 > h1);
}

void Game::Update(){
	SDL_Delay(20);
	if(SDL_PollEvent(&e) && e.type == SDL_MOUSEBUTTONDOWN){
		bird.dist = -15;
		window.chunkPlay(clickSound);
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
				window.chunkPlay(scoreSound);
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
		if(x.rect.x <= -100) entity.erase(entity.begin());
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
		SDL_Delay(10);
		bird.move();
		display();
		Update();
		if(!notLose()) quit = 1;
	}
	afterLose();
}

void Game::afterLose(){
	best_score = max(best_score, score);
	window.render(score_tex, {200, 200, 200, 100});
	window.render(score_tex, {600, 200, 325, 100});
	window.render("Score:" + to_String(score), 230, 230, {0 , 0, 0, 120});
	window.render("Best score:" + to_String(best_score), 650, 230, {0 , 0, 0, 120});
	window.render(replay_button, {450, 400, 100, 100});
	if(isPlayingMusic) window.render(sound_button, {900, 600, 100, 100});
	else window.render(nosound_button, {900, 600, 100, 100});
	window.display();
	while(1){
		int sign = getAction();
		if(sign == 3) {
			SDL_Delay(200);
			start();
			return;
		}
		else if(sign == 0){
			end();
			return;
		}
		else if(sign == 2){
			Sound();
			afterLose();
			return;
		}
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
				window.chunkPlay(explorationSound);
			}
		}
	}
	if(!bird.inside(WINDOW_WIDTH, WINDOW_HEIGHT)){
		window.chunkPlay(dieSound);
		return 0;
	}
	return ok;
}