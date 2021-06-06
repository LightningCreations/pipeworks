#ifndef PW_SDLAUDIOPLAYER_HPP
#define PW_SDLAUDIOPLAYER_HPP

#include <audioplayer.hpp>

namespace pipeworks {

class SDLAudioPlayer : public AudioPlayer {
  public:
    void set_callback(void(*callback)(void*,uint8_t*,int), void *userdata);
    void tick();
};

}

#endif // PW_SDLAUDIOPLAYER_HPP
