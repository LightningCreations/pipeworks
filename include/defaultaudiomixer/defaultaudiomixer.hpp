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
    uint64_t m_bgm_pos;
    uint64_t m_bgm_loop_start;
    uint64_t m_bgm_loop_end;
    const AudioData *m_bgm;
    uint64_t m_sfx_pos[SFX_COUNT];
    const AudioData *m_sfx[SFX_COUNT];
    std::mutex m_bgm_mutex;
    std::mutex m_sfx_mutex;
  public:
    DefaultAudioMixer();
    void fill_buffer(float*, int);
    void set_bgm(const AudioData*, uint64_t loop_start, uint64_t loop_end);
    // add_sfx in this implementation is a no-op
    void add_sfx(const AudioData*);
    void play_sfx(const AudioData*);
};

}

#endif // PW_DEFAULT_AUDIO_MIXER_HPP
