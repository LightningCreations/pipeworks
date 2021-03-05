#include <objects/emitter.hpp>

namespace pipeworks {

Emitter::Emitter(float x, float y, float z,
    float lifetime, ParticleParameter posx, ParticleParameter posy, ParticleParameter r, ParticleParameter g, ParticleParameter b):
    GameObject(x, y, z), m_enabled(false), m_lifetime(lifetime), m_posx(posx), m_posy(posy), m_r(r), m_g(g), m_b(b),
    m_rng(0) {} // Deterministically seeded for no good reason.
// Actually, there is a good reason: Testing in the future will want deterministic results.

void Emitter::set_enabled(bool enabled) {
    m_enabled = enabled;
}

void Emitter::render(Renderer &renderer) {
    if(m_enabled) {
        std::uniform_real_distribution sx(0,m_posx.sv);
        std::uniform_real_distribution sdx(0,m_posx.sdv);
        std::uniform_real_distribution sddx(0,m_posx.sddv);
        std::uniform_real_distribution sy(0,m_posy.sv);
        std::uniform_real_distribution sdy(0,m_posy.sdv);
        std::uniform_real_distribution sddy(0,m_posy.sddv);
        std::uniform_real_distribution sr(0,m_r.sv);
        std::uniform_real_distribution sdr(0,m_r.sdv);
        std::uniform_real_distribution sddr(0,m_r.sddv);
        std::uniform_real_distribution sg(0,m_g.sv);
        std::uniform_real_distribution sdg(0,m_g.sdv);
        std::uniform_real_distribution sddg(0,m_g.sddv);
        std::uniform_real_distribution sb(0,m_b.sv);
        std::uniform_real_distribution sdb(0,m_b.sdv);
        std::uniform_real_distribution sddb(0,m_b.sddv);
        m_particles.push_back(Particle{
            0,
            m_posx.v+m_x+sx(m_rng)-m_posx.sv/2, m_posx.dv+sdx(m_rng)-m_posx.sdv/2, m_posx.ddv+sddx(m_rng)-m_posx.sddv/2,
            m_posy.v+m_y+sy(m_rng)-m_posy.sv/2, m_posy.dv+sdy(m_rng)-m_posy.sdv/2, m_posy.ddv+sddy(m_rng)-m_posy.sddv/2,
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
            renderer.fill_rect(p.x + xoff, p.y + yoff, 0, 0, p.r*255, p.g*255, p.b*255, 255);
            p.x += p.dx * delta;
            p.y += p.dy * delta;
            p.r += p.dr * delta;
            p.g += p.dg * delta;
            p.b += p.db * delta;
            p.dx += p.ddx * delta;
            p.dy += p.ddy * delta;
            p.dr += p.ddr * delta;
            p.dg += p.ddg * delta;
            p.db += p.ddb * delta;
            itr++;
        }
    }
}

void Emitter::set_posx(ParticleParameter posx) {
    m_posx = posx;
}

void Emitter::set_posy(ParticleParameter posy) {
    m_posy = posy;
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
