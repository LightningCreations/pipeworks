#ifndef PW_SDLAUDIOPLAYER_HPP
#define PW_SDLAUDIOPLAYER_HPP

#include "../audioplayer.hpp"

namespace pipeworks {

class SDLAudioPlayer : public AudioPlayer {
  private:
    bool m_callback_set;
  public:
    SDLAudioPlayer();
    ~SDLAudioPlayer();
    void set_callback(void(*callback)(void*,float*,int), void *userdata);
    void tick();
};

}

#endif // PW_SDLAUDIOPLAYER_HPP
