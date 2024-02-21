#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "Renderer.h"

int main(int argc, char** args) {

    Renderer ren; 

    double deltaTimeTarget = 1.0f / 60.0f;

    double frameStart;
    double frameTime;

    while (globals::running) {

		frameStart = SDL_GetTicks();
		ren.update();

		frameTime = SDL_GetTicks() - frameStart;
 
		if (deltaTimeTarget > frameTime) {

			SDL_Delay(deltaTimeTarget - frameTime);

		}


	}

	ren.clean();

}