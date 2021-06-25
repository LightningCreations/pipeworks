#ifndef PW_AUDIO_MIXER_HPP
#define PW_AUDIO_MIXER_HPP

#include <cstdint>

#include "audiodata.hpp"

namespace pipeworks {

class AudioMixer {
  public:
    virtual ~AudioMixer() = 0;
    // Called by the Engine in the audio thread
    virtual void fill_buffer(float *buf, int len) = 0;
    // Called by the Engine in response to game code
    virtual void set_bgm(const AudioData *bgm, uint64_t loop_start, uint64_t loop_end) = 0;
    // Called by the Engine in response to game code
    // Needs to be called before play_sfx to actually register the effect
    virtual void add_sfx(const AudioData *bgm) = 0;
    // Called by the Engine in response to game code
    // Sound effect needs to be registered with add_sfx first
    virtual void play_sfx(const AudioData *bgm) = 0;
};

}

#endif // PW_AUDIO_MIXER_HPP
