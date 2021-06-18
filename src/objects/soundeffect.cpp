#include <cmath>
#include <objects/soundeffect.hpp>
#include <resourcemanager.hpp>

namespace pipeworks {

SoundEffect::SoundEffect(Engine &engine, const AudioData &data): GameObject(-INFINITY, -INFINITY, -INFINITY),
    m_engine(engine), m_data(&data), m_loaded(true) {
    m_engine.add_sfx(m_data);
}

SoundEffect::SoundEffect(Engine &engine, std::string resource): GameObject(-INFINITY, -INFINITY, -INFINITY),
    m_engine(engine), m_data(nullptr), m_resources{resource}, m_loaded(false) {
}

void SoundEffect::finished_loading() {
    m_data = &g_resourcemanager.audio_data(m_resources[0]);
    m_engine.add_sfx(m_data);
    m_loaded = true;
}

bool SoundEffect::is_loading() {
    return m_loaded;
}

std::vector<std::string>& SoundEffect::loadable_resources() {
    return m_resources;
}

void SoundEffect::play() {
    m_engine.play_sfx(m_data);
}

void SoundEffect::render(Renderer &renderer) {
    (void) renderer;
}

}
