#include <defaultaudiomixer.hpp>

namespace pipeworks {

DefaultAudioMixer::DefaultAudioMixer() {
}

void DefaultAudioMixer::fill_buffer(float *buf, int len) {
    for(int i = 0; i < len/2; i++) {
        buf[i*2] = 0;
        buf[i*2+1] = 0;
        {
            std::unique_lock<std::mutex> sfx_lock{m_sfx_mutex};
            for(int i = 0; i < SFX_COUNT; i++) {
                if(sfx[i]) {
                    buf[i*2] += 0.1f; // Temp
                    buf[i*2+1] += 0.1f;
                    sfx_pos[i]++;
                    if(sfx_pos[i] > 48000) {
                        sfx[i] = nullptr;
                    }
                }
            }
        }
    }
}

void DefaultAudioMixer::set_bgm(const AudioData *data) {
}

void DefaultAudioMixer::add_sfx(const AudioData *data) {
    (void) data; // This function doesn't need to do anything
}

void DefaultAudioMixer::play_sfx(const AudioData *data) {
    std::unique_lock<std::mutex> sfx_lock{m_sfx_mutex};
    for(int i = 0; i < SFX_COUNT; i++) {
        if(!sfx[i]) { // sfx will be zeroed when completed
            sfx[i] = data;
            sfx_pos[i] = 0;
            return;
        }
    }
    sfx[0] = data; // Most likely to be the furthest through playing
}

}
