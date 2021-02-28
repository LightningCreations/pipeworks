#include <objects/emitter.hpp>

namespace pipeworks {

Emitter::Emitter(float x, float y, float z,
    float lifetime, ParticleParameter posx, ParticleParameter posy, ParticleParameter r, ParticleParameter g, ParticleParameter b):
    GameObject(x, y, z), m_enabled(false), m_lifetime(lifetime), m_posx(posx), m_posy(posy), m_r(r), m_g(g), m_b(b) {}

void Emitter::set_enabled(bool enabled) {
    m_enabled = enabled;
}

} // namespace pipeworks
