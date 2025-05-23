#include "Rain.h"

Rain::Rain() {
    effectSound = LoadSound("image/Sound/rain.wav");
}

Rain::~Rain() {
    UnloadSound(effectSound);
}

void Rain::update(int screenWidth, int screenHeight) {
    for (int i = 0; i < 20; ++i) {
        if (GetRandomValue(0, 200) < 10) {
            float x = static_cast<float>(GetRandomValue(0, screenWidth + 200));
            Color randomColor = BLUE;
            particles.push_back({Vector2{x, 0}, randomColor, static_cast<float>(GetRandomValue(-45, 45))});
        }
    }
}

void Rain::drawTo() {
    for (auto &particle : particles) {
        particle.position.x -= 4;
        particle.position.y += 7;

        DrawRectanglePro({particle.position.x, particle.position.y, particleShape.width, particleShape.height},
                         Vector2{particleShape.width / 2, particleShape.height / 2},
                         particle.rotation,
                         particle.color);
    }
    const float screenHeight = static_cast<float>(GetScreenHeight());

    for (auto it = particles.begin(); it != particles.end(); /* no increment here */) {
        if (it->position.y > screenHeight) {
            it = particles.erase(it);
        } else {
            ++it;
        }
    }
}
