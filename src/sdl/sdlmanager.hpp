#ifndef SDLMANAGER_HPP
#define SDLMANAGER_HPP

namespace pipeworks {

class SDLManager {
  public:
    SDLManager();
    ~SDLManager();
    void verify_active();
    int init_video();
    void quit_video();
};

SDLManager *get_global_sdlmanager();

}

#endif
