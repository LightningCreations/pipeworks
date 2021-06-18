#include <defaultaudiomixer.hpp>

namespace pipeworks {

DefaultAudioMixer::DefaultAudioMixer(): sfx{}, sfx_pos{} {}

void DefaultAudioMixer::fill_buffer(float *buf, int len) {
    for(int i = 0; i < len/2; i++) {
        buf[i*2] = 0;
        buf[i*2+1] = 0;
        {
            std::unique_lock<std::mutex> sfx_lock{m_sfx_mutex};
            for(int j = 0; j < SFX_COUNT; j++) {
                if(sfx[j]) {
                    std::vector<float> data = sfx[j]->data();
                    buf[i*2] += data[sfx_pos[j]*2];
                    buf[i*2+1] += data[sfx_pos[j]*2+1];
                    sfx_pos[j]++;
                    if(sfx_pos[j] > (data.size()/2)) {
                        sfx[j] = nullptr;
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
    if(data->data().size() == 0) return; // If there is no sound, don't play
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
