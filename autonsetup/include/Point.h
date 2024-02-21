#pragma once

#include "Globals.h"
#include "Drawer.h"

struct Point {

public:

    std::size_t x, y;
    std::size_t radius;

    SDL_Color color = Drawer::white;
    

    inline Point(std::size_t x, std::size_t y, std::size_t radius) : x(x), y(y), radius(radius) {}

    inline void draw() {
        Drawer::drawCircleFilled(x, y, radius, color);
    }


};