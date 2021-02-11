#include "starfieldbackground.hpp"

#include <random>

namespace fotc {

StarfieldBackground::StarfieldBackground(float x, float y, float z) noexcept: x(x), y(y) {
    (void) z; // This is sorting Z, not star Z. And there is no sorting.
    std::random_device rd; // Doesn't need to be cryptographically seeded or anything
    std::mt19937 gen(rd()); // The actual algorithm doesn't need to be cryptographic either
    std::uniform_real_distribution<float> random(-1.f,1.f);
    for(int i = 0; i < STARFIELD_NUM_STARS; i++) {
        starz[i] = i + 1; // Easier to get an even distribution of stars when Z coordinates are deterministic
        stary[i] = random(gen) * starz[i]; // Normalized from -1 to 1 in screen space
        starx[i] = random(gen) * starz[i] * 2; // Normalized from -2 to 2 in screen space (the screen is likely to be wider than it is tall)
    }
}

void StarfieldBackground::render(Renderer &renderer) {
    renderer.fill_rect(-2, -2, 4, 4, 0, 0, 0, 255); // Clear out
    for(int i = 0; i < STARFIELD_NUM_STARS; i++) {
        renderer.fill_rect(starx[i]/starz[i], stary[i]/starz[i], // Perspective divide
                           0, 0, // No width; always drawn as one pixel
                           255, 255, 255, 255 // All stars are clearly white. Redshift and blueshift clearly do not exist and definitely won't just be implemented later instead.
        );

        // FIXME: TEMP CODE (awaiting proper responsive scrolling)
        starx[i] += (renderer.key_down('a') ? 0.1f : 0) - (renderer.key_down('d') ? 0.1f : 0);
        stary[i] += (renderer.key_down('w') ? 0.1f : 0) - (renderer.key_down('s') ? 0.1f : 0);
        if(starx[i]/starz[i] >= 2) starx[i] -= starz[i] * 4; // * 4 because we're going from 2 to -2
        if(starx[i]/starz[i] < -2) starx[i] += starz[i] * 4;
        if(stary[i]/starz[i] >= 1) stary[i] -= starz[i] * 2; // * 2 because we're going from 1 to -1
        if(stary[i]/starz[i] < -1) stary[i] += starz[i] * 2;
    }
}

} // namespace fotc
