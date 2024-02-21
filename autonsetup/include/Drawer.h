#pragma once

#include "Globals.h"

class Drawer {

public:

static inline SDL_Color white = SDL_Color{255, 255, 255, 255};
static inline SDL_Color red = SDL_Color{255, 0, 0, 255};

static void drawCircle(int32_t centreX, int32_t centreY, int32_t radius, SDL_Color color = white)
{
using namespace globals;

    SDL_Color prev;

    SDL_GetRenderDrawColor(globals::renderer, &prev.r, &prev.g, &prev.b, &prev.a);

    SDL_SetRenderDrawColor(globals::renderer, color.r, color.g, color.b, color.a);

   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }

    SDL_SetRenderDrawColor(globals::renderer, prev.r, prev.g, prev.b, prev.a);
}

static void drawCircleFilled(std::size_t x, std::size_t y, std::size_t radius, SDL_Color color = white)  {

    using namespace globals;

    SDL_Color prev;

    SDL_GetRenderDrawColor(globals::renderer, &prev.r, &prev.g, &prev.b, &prev.a);

    SDL_SetRenderDrawColor(globals::renderer, color.r, color.g, color.b, color.a);
    
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }

    SDL_SetRenderDrawColor(globals::renderer, prev.r, prev.g, prev.b, prev.a);


}

static void drawLine(SDL_Point first, SDL_Point second, SDL_Color color = white) {

    SDL_Color prev;

    SDL_GetRenderDrawColor(globals::renderer, &prev.r, &prev.g, &prev.b, &prev.a);

    SDL_SetRenderDrawColor(globals::renderer, color.r, color.g, color.b, color.a);

    SDL_RenderDrawLine(globals::renderer, first.x, first.y, second.x, second.y);

    SDL_SetRenderDrawColor(globals::renderer, prev.r, prev.g, prev.b, prev.a);
}


};