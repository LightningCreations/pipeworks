#include <sdlaudioplayer.hpp>

#include <sdlmanager.hpp>

#include <SDL.h>

namespace pipeworks {

class SDLAudioManager {
  public:
    SDLAudioManager();
    ~SDLAudioManager();
    void verify_active();
};

SDLAudioManager::SDLAudioManager() {
    global_sdlmanager()->init_video();
}

SDLAudioManager::~SDLAudioManager() {
    global_sdlmanager()->quit_video();
}

void SDLAudioManager::verify_active() {
    global_sdlmanager()->verify_active();
}

static SDLAudioManager s_audio_manager;

SDLAudioPlayer::SDLAudioPlayer(): m_callback_set(false) {
    s_audio_manager.verify_active();
}

// NOTE: API is likely to change in the future
// I don't particularly like this, tbh
void SDLAudioPlayer::set_callback(void(*callback)(void*,float*,int), void *userdata) {
    if(m_callback_set) SDL_CloseAudio();
    SDL_AudioSpec format;
    SDL_memset(&format, 0, sizeof(format));
    format.freq = 48000;
    format.format = AUDIO_F32;
    format.channels = 2;
    format.samples = 1024;
    format.callback = (SDL_AudioCallback) callback;
    format.userdata = userdata;
    if(SDL_OpenAudio(&format, nullptr) != 0) {
        throw "Couldn't open audio device";
    }
    SDL_PauseAudio(0);
    m_callback_set = true;
}

void SDLAudioPlayer::tick() {
    // Don't need to do anything
}

SDLAudioPlayer::~SDLAudioPlayer() {
    if(m_callback_set) SDL_CloseAudio();
    s_audio_manager.verify_active();
}

}
