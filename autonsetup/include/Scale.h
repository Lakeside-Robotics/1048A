#pragma once

#include "Globals.h"
#include <optional>
#include <math.h> 

class Scale {
public:

    double pixelToInch;
    int index = -1;

    std::optional<SDL_Point> first;
    std::optional<SDL_Point> second;

    void calculate(int inches) {

        if (!first.has_value() && !second.has_value())
            return;

        double pixels = std::sqrt( (first.value().x - second.value().x) * (first.value().x - second.value().x) + (first.value().y - second.value().y) * (first.value().y - second.value().y));
        pixelToInch = inches / pixels;


    }

    void clear() {
        first = std::nullopt;
        second = std::nullopt;
    }


};