#include <bits/stdc++.h>

#include "game.h"

 
using namespace std;

int random(int _max){
  srand(time(NULL));
  return rand() % _max;
}

Entity Rand_Entity(){
	Entity res({1000, random(700), 50, 50}, random(4) != 2);
	return res;
}

int main(int argc, char *argv[]){
	Entity x = Rand_Entity();
	cout << x.type;
	Game game;
	game.start();

}