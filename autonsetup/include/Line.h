#pragma once

#include <optional>

#include "Globals.h"
#include "Point.h"
#include "Drawer.h"

class Line {

public:

    SDL_Point first, second;


    inline Line(SDL_Point first, SDL_Point second) : first(first), second(second) {}

    inline void draw(SDL_Color color = Drawer::white) {
        Drawer::drawLine(first, second, color);
    }


};

struct LineHandler {

std::optional<SDL_Point> first;
std::optional<SDL_Point> second;

inline void clear() {
    first = std::nullopt;
    second = std::nullopt;
}


};