#include <cmath>
#include <objects/emitter.hpp>

namespace pipeworks {

Emitter::Emitter(float x, float y, float z,
    float lifetime, ParticleParameter v, ParticleParameter t, ParticleParameter r, ParticleParameter g, ParticleParameter b):
    GameObject(x, y, z), m_enabled(false), m_lifetime(lifetime), m_v(v), m_t(t), m_r(r), m_g(g), m_b(b),
    m_rng(0) {} // Deterministically seeded for no good reason.
// Actually, there is a good reason: Testing in the future will want deterministic results.

void Emitter::set_enabled(bool enabled) {
    m_enabled = enabled;
}

void Emitter::render(Renderer &renderer) {
    if(m_enabled) {
        std::uniform_real_distribution sv(0.f,m_v.sv);
        std::uniform_real_distribution sdv(0.f,m_v.sdv);
        std::uniform_real_distribution sddv(0.f,m_v.sddv);
        std::uniform_real_distribution st(0.f,m_t.sv);
        std::uniform_real_distribution sdt(0.f,m_t.sdv);
        std::uniform_real_distribution sddt(0.f,m_t.sddv);
        std::uniform_real_distribution sr(0.f,m_r.sv);
        std::uniform_real_distribution sdr(0.f,m_r.sdv);
        std::uniform_real_distribution sddr(0.f,m_r.sddv);
        std::uniform_real_distribution sg(0.f,m_g.sv);
        std::uniform_real_distribution sdg(0.f,m_g.sdv);
        std::uniform_real_distribution sddg(0.f,m_g.sddv);
        std::uniform_real_distribution sb(0.f,m_b.sv);
        std::uniform_real_distribution sdb(0.f,m_b.sdv);
        std::uniform_real_distribution sddb(0.f,m_b.sddv);
        m_particles.push_back(Particle{
            0, m_x, m_y,
            m_v.v+sv(m_rng)-m_v.sv/2, m_v.dv+sdv(m_rng)-m_v.sdv/2, m_v.ddv+sddv(m_rng)-m_v.sddv/2,
            m_t.v+st(m_rng)-m_t.sv/2, m_t.dv+sdt(m_rng)-m_t.sdv/2, m_t.ddv+sddt(m_rng)-m_t.sddv/2,
            m_r.v+sr(m_rng)-m_r.sv/2, m_r.dv+sdr(m_rng)-m_r.sdv/2, m_r.ddv+sddr(m_rng)-m_r.sddv/2,
            m_g.v+sg(m_rng)-m_g.sv/2, m_g.dv+sdg(m_rng)-m_g.sdv/2, m_g.ddv+sddg(m_rng)-m_g.sddv/2,
            m_b.v+sb(m_rng)-m_b.sv/2, m_b.dv+sdb(m_rng)-m_b.sdv/2, m_b.ddv+sddb(m_rng)-m_b.sddv/2
        });
    }
    float delta = 1.0f/60; // Delta correction doesn't exist yet, so we have a placeholder delta
    float xoff = x() - m_x; // There should be a way of doing this that makes more sense.
    float yoff = y() - m_y; // That's a problem for future me.
    for(std::vector<Particle>::iterator itr = m_particles.begin(); itr < m_particles.end();) {
        Particle &p = *itr;
        p.timer += delta;
        if(p.timer >= m_lifetime) {
            itr = m_particles.erase(itr);
        } else {
            renderer.fill_rect(p.x + xoff, p.y + yoff, 0, 0, (uint8_t) (p.r*255), (uint8_t) (p.g*255), (uint8_t) (p.b*255), 255);
            p.x += p.v * cos(p.t) * delta;
            p.y += p.v * sin(p.t) * delta;
            p.v += p.dv * delta;
            p.t += p.dt * delta;
            p.r += p.dr * delta;
            p.g += p.dg * delta;
            p.b += p.db * delta;
            p.dv += p.ddv * delta;
            p.dt += p.ddt * delta;
            p.dr += p.ddr * delta;
            p.dg += p.ddg * delta;
            p.db += p.ddb * delta;
            itr++;
        }
    }
}

void Emitter::set_v(ParticleParameter v) {
    m_v = v;
}

void Emitter::set_t(ParticleParameter t) {
    m_t = t;
}

void Emitter::set_r(ParticleParameter r) {
    m_r = r;
}

void Emitter::set_g(ParticleParameter g) {
    m_g = g;
}

void Emitter::set_b(ParticleParameter b) {
    m_g = b;
}

} // namespace pipeworks
