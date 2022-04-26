#include "entity.h"

using namespace std;

int Rand(int _max){
  srand(time(NULL));
  return rand() % _max;
}

Entity::Entity(SDL_Rect _rect, int _type){
	this -> rect = _rect;
	this -> type = _type;
}

Entity::Entity(){
	Entity x({1080, Rand(720), 50, 50}, Rand(4) != 2);
	this -> rect = x.rect;
	this -> type = x.type;
}

void Entity::move(){
	(this -> rect).x -= dist;
}

bool Entity::inside(int w, int h){
	return (this->rect).x >= 0 && (this->rect).y >= 0 &&  (this->rect).x + (this->rect).w <= w &&  (this->rect).y + (this->rect).h <= h;
}