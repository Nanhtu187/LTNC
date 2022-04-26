#include "bird.h"

using namespace std;

void Bird::move(){
	(this->rect).y += dist;
	(this->rect).y = max(0, (this->rect).y);
}

Bird::Bird(int _x, int _y, int _size){
	(this -> rect).x = _x;
	(this -> rect).y = _y;
	(this -> rect).w = _size;
	(this -> rect).h = _size;
	this -> dist = 0;
}

Bird::Bird(){}

bool Bird::inside(int w, int h){
	return (this->rect).x + (this->rect).w <= w &&  (this->rect).y + (this->rect).h <= h;
}

void Bird::reset(int _x, int _y, int _size){
	(this -> rect).x = _x;
	(this -> rect).y = _y;
	(this -> rect).w = _size;
	(this -> rect).h = _size;
	this -> dist = 0;
}

