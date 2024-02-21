#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <atomic>

namespace globals {

	inline SDL_Renderer* renderer = nullptr;
	inline int TEX_WIDTH_PIXELS, TEX_HEIGHT_PIXELS;
	inline std::atomic<bool> running = true;

}