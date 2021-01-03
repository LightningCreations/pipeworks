#include <sdlrenderer.hpp>

#include <sdlmanager.hpp>

#include <SDL.h>

namespace pipeworks {

class SDLRenderManager {
  public:
    SDLRenderManager();
    ~SDLRenderManager();
    void verify_active();
};

SDLRenderManager::SDLRenderManager() {
    get_global_sdlmanager()->init_video();
}

SDLRenderManager::~SDLRenderManager() {
    get_global_sdlmanager()->quit_video();
}

void SDLRenderManager::verify_active() {
    get_global_sdlmanager()->verify_active();
}

static SDLRenderManager render_manager;

SDLRenderer::SDLRenderer() {
    render_manager.verify_active(); // Initialize video if it isn't initialized already
}

SDLRenderer::~SDLRenderer() {
    render_manager.verify_active(); // Make sure the manager doesn't get destructed too soon (it shouldn't, I'm being paranoid)
}

}
