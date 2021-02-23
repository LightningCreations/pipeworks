#include "starfieldbackground.hpp"

#include <random>

namespace fotc {

void call_scroll(void *obj, void *data,pipeworks::EventType,pipeworks::Engine&) {
    ((StarfieldBackground*) obj)->scroll(data);
}

StarfieldBackground::StarfieldBackground(float z, Engine &engine) noexcept: x(0), y(0) {
    (void) z; // This is sorting Z, not star Z. And there is no sorting.
    std::random_device rd; // Doesn't need to be cryptographically seeded or anything
    std::mt19937 gen(rd()); // The actual algorithm doesn't need to be cryptographic either
    std::uniform_real_distribution<float> random(-1.f,1.f);
    for(int i = 0; i < STARFIELD_NUM_STARS; i++) {
        starz[i] = i + 1; // Easier to get an even distribution of stars when Z coordinates are deterministic
        stary[i] = random(gen) * starz[i]; // Normalized from -1 to 1 in screen space
        starx[i] = random(gen) * starz[i] * 2; // Normalized from -2 to 2 in screen space (the screen is likely to be wider than it is tall)
    }
    engine.register_event(std::unique_ptr<Event>(new Event(EventType::Frame, &call_scroll, this)));
}

void StarfieldBackground::scroll(void *eventdata) {
    if(!renderer) return; // Because currently the renderer handles key state. @InfernoDeity please fix
    float xoff = x - prev_x;
    float yoff = y - prev_y;
    Renderer &renderer = *this->renderer;
    for(int i = 0; i < STARFIELD_NUM_STARS; i++) {
        starx[i] += xoff;
        stary[i] += yoff;
        if(starx[i]/starz[i] >= 2) starx[i] -= starz[i] * 4; // * 4 because we're going from 2 to -2
        if(starx[i]/starz[i] < -2) starx[i] += starz[i] * 4;
        if(stary[i]/starz[i] >= 1) stary[i] -= starz[i] * 2; // * 2 because we're going from 1 to -1
        if(stary[i]/starz[i] < -1) stary[i] += starz[i] * 2;
    }
    prev_x = x;
    prev_y = y;
}

void StarfieldBackground::set_x(float x) {
    this->x = x;
}

void StarfieldBackground::set_y(float y) {
    this->y = y;
}

void StarfieldBackground::render(Renderer &renderer) {
    this->renderer = &renderer;
    renderer.fill_rect(-2, 2, 4, 4, 0, 0, 0, 255); // Clear out
    for(int i = 0; i < STARFIELD_NUM_STARS; i++) {
        renderer.fill_rect(starx[i]/starz[i], stary[i]/starz[i], // Perspective divide
                           0, 0, // No width; always drawn as one pixel
                           255, 255, 255, 255 // All stars are clearly white. Redshift and blueshift clearly do not exist and definitely won't just be implemented later instead.
        );
    }
}

} // namespace fotc
