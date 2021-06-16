#ifndef PW_DEFAULT_AUDIO_MIXER_HPP
#define PW_DEFAULT_AUDIO_MIXER_HPP

#include "../audiomixer.hpp"

#include <cstdint>
#include <map>
#include <mutex>

namespace pipeworks {

class DefaultAudioMixer : public AudioMixer {
  private:
    const static int SFX_COUNT = 256;
    uint64_t bgm_pos;
    const AudioData *bgm;
    uint64_t sfx_pos[SFX_COUNT];
    const AudioData *sfx[SFX_COUNT];
    std::mutex m_sfx_mutex;
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
