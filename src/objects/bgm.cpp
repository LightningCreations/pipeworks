#include <cmath>
#include <objects/bgm.hpp>
#include <resourcemanager.hpp>

namespace pipeworks {

BGM::BGM(Engine &engine, const AudioData &data, uint64_t loop_start, uint64_t loop_end): GameObject(-INFINITY, -INFINITY, -INFINITY),
    m_engine(engine), m_data(&data), m_loop_start(loop_start), m_loop_end(loop_end), m_loaded(true) {
    if(m_loop_end > m_data->data().size()) m_loop_end = m_data->data().size();
}

BGM::BGM(Engine &engine, std::string resource, uint64_t loop_start, uint64_t loop_end): GameObject(-INFINITY, -INFINITY, -INFINITY),
    m_engine(engine), m_data(nullptr), m_resources{resource}, m_loop_start(loop_start), m_loop_end(loop_end), m_loaded(false) {
}

void BGM::finished_loading() {
    m_data = &g_resourcemanager.audio_data(m_resources[0]);
    if(m_loop_end > m_data->data().size()) m_loop_end = m_data->data().size();
    m_loaded = true;
    play();
}

bool BGM::is_loading() {
    return m_loaded;
}

std::vector<std::string>& BGM::loadable_resources() {
    return m_resources;
}

void BGM::play() {
    if(m_data)
        m_engine.set_bgm(m_data, m_loop_start, m_loop_end);
}

void BGM::render(Renderer &renderer) {
    (void) renderer;
}

}
