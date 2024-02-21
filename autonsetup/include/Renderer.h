#pragma once

#include <stdexcept>
#include <vector>

#include "Globals.h"
#include "Point.h"
#include "Line.h"
#include "Scale.h"

#define PIXEL 20

class Renderer {

private:

enum class State {

    POINT, 
    LINE,
    SCALE


};

private:

    SDL_Window* window;
    SDL_Event event;
    std::vector<Point> points;
    std::vector<Line> lines;
    State state = State::POINT;

    LineHandler lh;
    Scale scale;

    SDL_Texture* field;

public:

inline Renderer() {

    using namespace globals;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		window = SDL_CreateWindow("autonsetup", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
		if (!window) {
		    throw std::runtime_error("unable to initalize window");
		}
 		
 		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			globals::renderer = renderer;
		}
        else {
            throw std::runtime_error("unable to initalize renderer");
        }


    }
    else {
        throw std::runtime_error("unable to initalize sdl");
    }

    field = nullptr;
    
    if (field = IMG_LoadTexture(renderer, "res/field.png"); field == nullptr)
        throw std::runtime_error("add field png to resources folder"); 

    SDL_Rect src;
    SDL_Rect dest;

    src.x = 0;
    src.y = 0;
    
    SDL_QueryTexture(field, NULL, NULL, &src.w, &src.h);

    dest.x = 0;
    dest.y = 0;
    dest.w = 600;
    dest.h = 600;

    if (SDL_RenderCopy(renderer, field, &src, &dest) < 0) 
        throw std::runtime_error("unable to render texture");
    


}

inline void update() {

    SDL_Rect src;
    SDL_Rect dest;

    src.x = 0;
    src.y = 0;
    
    SDL_QueryTexture(field, NULL, NULL, &src.w, &src.h);

    dest.x = 0;
    dest.y = 0;
    dest.w = 600;
    dest.h = 600;

    if (SDL_RenderCopy(globals::renderer, field, &src, &dest) < 0) 
        throw std::runtime_error("unable to render texture");

    SDL_PollEvent(&event);

    switch (event.type) {

        case SDL_QUIT:

            globals::running = false;
            break;

        case SDL_MOUSEBUTTONDOWN:

            {
            
            SDL_MouseButtonEvent& mb = event.button;

            if (state == State::POINT) {
                points.emplace_back(Point(mb.x, mb.y, 7));
            }

            else if (state == State::LINE) {
                for (Point& point : points) {
                    if ( ((mb.x - point.x) * (mb.x - point.x) + (mb.y- point.y) * (mb.y - point.y)) < (point.radius * point.radius) ) {
                        if (lh.first.has_value()) {
                           // std::cout << "second set";
                            lh.second = SDL_Point{(int)point.x, (int)point.y};
                            lines.emplace_back(Line{SDL_Point{lh.first.value().x, lh.first.value().y}, SDL_Point{lh.second.value().x, lh.second.value().y}});
                            lh.clear();
                        }
                        else {
                            lh.first = SDL_Point{(int)point.x, (int)point.y};
                           // std::cout << "first set";
                        }
                    }
                }
            }

            if (state == State::SCALE) {

                if (scale.first.has_value()) {
                    // std::cout << "second set";
                    scale.second = SDL_Point{(int)mb.x, (int)mb.y};
                    scale.calculate(20);
                    scale.clear(); 

                }
                else {
                    scale.first = SDL_Point{(int)mb.x, (int)mb.y};
                    lines.emplace_back(Line{SDL_Point{scale.first.value().x, scale.first.value().y}, SDL_Point{mb.x, mb.y}});
                    scale.index = lines.size() - 1;
                }      



            }

            }

            break;
        
        case SDL_KEYDOWN:

            if (event.key.keysym.sym == SDLK_l)
                state = State::LINE;
            if (event.key.keysym.sym == SDLK_p)
                state = State::POINT;
            if (event.key.keysym.sym == SDLK_s)
                state = State::SCALE;
            break;





    }

    int mX;
    int mY;

    SDL_GetMouseState(&mX, &mY);

    if (state == State::LINE) {

        for (Point& point : points) {

            if ( ((mX - point.x) * (mX - point.x) + (mY - point.y) * (mY - point.y)) < (point.radius * point.radius) ) {

                point.color = Drawer::red;
            }
            else {
                point.color = Drawer::white;
            }
        }



    }

    // if (scale.index != -1 && scale.first.has_value()) {
    //     lines[scale.index] = Line{SDL_Point{scale.first.value().x, scale.first.value().y}, SDL_Point{mX, mY} };
    // }


    for (Point& point : points) {
        point.draw();
    }

    for (Line& line : lines) {
        line.draw();
    }

    SDL_RenderPresent(globals::renderer);



}

inline void clean() {
    SDL_DestroyWindow(window);
	SDL_DestroyRenderer(globals::renderer);
	SDL_Quit();
}

};