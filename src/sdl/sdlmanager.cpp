#include "sdlmanager.hpp" // Internal class

#include <SDL.h>

namespace pipeworks {

static SDLManager g_sdlmanager;

SDLManager *get_global_sdlmanager() {
    return &g_sdlmanager;
}

SDLManager::SDLManager() {
    SDL_Init(0);
}

void SDLManager::verify_active() { // Stub function to verify the object doesn't get destructed too soon
}

int SDLManager::init_video() {
    return SDL_InitSubSystem(SDL_INIT_VIDEO);
}

void SDLManager::quit_video() {
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDLManager::~SDLManager() {
    SDL_Quit();
}

}
