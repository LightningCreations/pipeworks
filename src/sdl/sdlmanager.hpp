#ifndef SDLMANAGER_HPP
#define SDLMANAGER_HPP

namespace pipeworks {

class SDLManager {
  public:
    SDLManager();
    ~SDLManager();
    void verify_active();
    int init_audio();
    int init_video();
    void quit_audio();
    void quit_video();
};

SDLManager *global_sdlmanager();

}

#endif
