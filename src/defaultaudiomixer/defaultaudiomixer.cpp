#include <defaultaudiomixer.hpp>

namespace pipeworks {

DefaultAudioMixer::DefaultAudioMixer(): m_sfx{}, m_sfx_pos{}, m_bgm{}, m_bgm_pos{} {}

void DefaultAudioMixer::fill_buffer(float *buf, int len) {
    for(int i = 0; i < len/2; i++) {
        {
            std::unique_lock<std::mutex> bgm_lock{m_bgm_mutex};
            if(m_bgm) {
                buf[i*2] = m_bgm->data()[m_bgm_pos*2];
                buf[i*2+1] = m_bgm->data()[m_bgm_pos*2+1];
                m_bgm_pos++;
                if(m_bgm_pos >= m_bgm_loop_end) {
                    m_bgm_pos = m_bgm_loop_start;
                }
            } else {
                buf[i*2] = 0;
                buf[i*2+1] = 0;
            }
        }
        {
            std::unique_lock<std::mutex> sfx_lock{m_sfx_mutex};
            for(int j = 0; j < SFX_COUNT; j++) {
                if(m_sfx[j]) {
                    const std::vector<float> &data = m_sfx[j]->data();
                    buf[i*2] += data[m_sfx_pos[j]*2];
                    buf[i*2+1] += data[m_sfx_pos[j]*2+1];
                    m_sfx_pos[j]++;
                    if(m_sfx_pos[j] >= (data.size()/2)) {
                        m_sfx[j] = nullptr;
                    }
                }
            }
        }
    }
}

void DefaultAudioMixer::set_bgm(const AudioData *data, uint64_t loop_start, uint64_t loop_end) {
    std::unique_lock<std::mutex> bgm_lock{m_bgm_mutex};
    m_bgm = data;
    m_bgm_loop_start = loop_start;
    m_bgm_loop_end = loop_end;
    m_bgm_pos = 0;
}

void DefaultAudioMixer::add_sfx(const AudioData *data) {
    (void) data; // This function doesn't need to do anything
}

void DefaultAudioMixer::play_sfx(const AudioData *data) {
    if(!data) return;
    if(data->data().size() == 0) return; // If there is no sound, don't play
    std::unique_lock<std::mutex> sfx_lock{m_sfx_mutex};
    for(int i = 0; i < SFX_COUNT; i++) {
        if(!m_sfx[i]) { // sfx will be zeroed when completed
            m_sfx[i] = data;
            m_sfx_pos[i] = 0;
            return;
        }
    }
    m_sfx[0] = data; // Most likely to be the furthest through playing
}

}
