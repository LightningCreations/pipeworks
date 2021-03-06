#include "sdlmanager.hpp" // Internal class

#include <SDL.h>

namespace pipeworks {

SDLManager *global_sdlmanager() {
    static SDLManager g_sdlmanager;
    return &g_sdlmanager;
}

SDLManager::SDLManager() {
    SDL_Init(0);
}

void SDLManager::verify_active() { // Stub function to verify the object doesn't get destructed too soon
}

int SDLManager::init_audio() {
    return SDL_InitSubSystem(SDL_INIT_AUDIO);
}

int SDLManager::init_video() {
    return SDL_InitSubSystem(SDL_INIT_VIDEO);
}

void SDLManager::quit_audio() {
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void SDLManager::quit_video() {
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDLManager::~SDLManager() {
    SDL_Quit();
}

}
