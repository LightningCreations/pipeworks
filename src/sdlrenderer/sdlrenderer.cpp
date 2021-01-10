#include <sdlrenderer.hpp>

#include <engine.hpp>
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

void SDLRenderer::open_window() {
    close_window(); // Just in case
    m_window = SDL_CreateWindow("Pipeworks Engine " PW_VERSION, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 1280, 720);
    m_pixels = new uint8_t[1280*720*4]; // Sorry about the new
}

void SDLRenderer::close_window() {
    if(m_pixels) delete[] m_pixels;
    m_pixels = nullptr;
    if(m_texture) SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
    if(m_renderer) SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
    if(m_window) SDL_DestroyWindow(m_window);
    m_window = nullptr;
}

bool SDLRenderer::is_close_requested() {
    return m_is_close_requested;
}

void SDLRenderer::render_poll() {
    for(Scene scene : active_scenes) {
        for(GameObject *object : scene.get_objects()) {
            object->render(*this); // TODO: Add special-casing for common GameObjects
        }
    }

    SDL_UpdateTexture(m_texture, NULL, &*m_pixels, 1280*4);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer); // Also syncs SDL-side

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) m_is_close_requested = true;
    }
}

void SDLRenderer::sync(uint32_t fps) {
    uint32_t cur_time = SDL_GetTicks();
    if(cur_time < next_time) SDL_Delay(next_time - cur_time);
    else next_time = cur_time; // If we're behind, stop being behind
    next_time += 1000/fps;
}

void SDLRenderer::set_active_scene_list(std::vector<Scene> scenes) {
    active_scenes = scenes;
    // No further processing needed
}

void SDLRenderer::set_width(uint32_t width) {
    this->width = width;
}

void SDLRenderer::set_height(uint32_t height) {
    this->height = height;
}

uint32_t SDLRenderer::get_width() {
    return width;
}

uint32_t SDLRenderer::get_height() {
    return height;
}

void SDLRenderer::fill_rect(float x, float y, float width, float height, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    // FIXME: Stub
}

}
