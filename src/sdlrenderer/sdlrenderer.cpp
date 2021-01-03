#include <sdlrenderer.hpp>

#include <SDL.h>

namespace pipeworks {

SDLRenderer::SDLRenderer() {
    static bool sdl_video_initialized = false;
    if(!sdl_video_initialized) {
        SDL_Init(SDL_INIT_VIDEO);
        sdl_video_initialized = true;
    }
}

}
