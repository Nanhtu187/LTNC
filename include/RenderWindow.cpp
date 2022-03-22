#include "RenderWindow.h"

using namespace std;


RenderWindow::RenderWindow(string title, int W, int H) :window(NULL), renderer(NULL){
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);

	if (window == NULL){
		cout << "Window failed to init. Error: " << SDL_GetError() << '\n';
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
}

SDL_Texture* RenderWindow::loadTexture(string path){
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else{
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL ){
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    return newTexture;
}

void RenderWindow::quit(){
	//TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void RenderWindow::clear(){
	SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::render(SDL_Texture* tex, SDL_Rect rect){
	SDL_RenderCopy(renderer, tex, NULL, &rect);
}
void RenderWindow::render(SDL_Texture* tex){
	SDL_RenderCopy(renderer, tex, NULL, NULL);
}