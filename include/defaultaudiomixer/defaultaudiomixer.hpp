#ifndef PW_DEFAULT_AUDIO_MIXER_HPP
#define PW_DEFAULT_AUDIO_MIXER_HPP

#include "../audiomixer.hpp"

#include <cstdint>
#include <map>

namespace pipeworks {

class DefaultAudioMixer : public AudioMixer {
  private:
    uint64_t bgm_pos;
    const AudioData *bgm;
    uint64_t sfx_pos[256];
    const AudioData *sfx[256];
  public:
    DefaultAudioMixer();
    void fill_buffer(float*, int);
    void set_bgm(const AudioData*);
    // add_sfx in this implementation is a no-op
    void add_sfx(const AudioData*);
    void play_sfx(const AudioData*);
};

}

#endif // PW_DEFAULT_AUDIO_MIXER_HPP
