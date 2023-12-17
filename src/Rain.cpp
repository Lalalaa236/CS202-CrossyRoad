#include "rain.h"
#include "MusicManager.h"
#include <algorithm>
Rain::Rain() {
    isToggleSound = false;
    raindropShape.width = 4;
    raindropShape.height = 7;
    state = 0;
    rainSound = LoadSound("image/Sound/rain.wav");
}

void Rain::setState(int st) {
    state = st;
    if (state == 1) {
        PlaySound(rainSound);
        if (MusicManager::getManager().getIsSoundOn()) {
            MusicManager::getManager().toggleSound();
            isToggleSound = true;
        }
    } 
    if (state == -1 || state == 0){
        if (isToggleSound) {
            MusicManager::getManager().toggleSound();
            isToggleSound = false;
        }
        StopSound(rainSound);
    }
}


int Rain::getState() {
    return state;
}

void Rain::update(int screenWidth, int screenHeight) {
    for (int i = 0; i < 20; ++i) {
        if (GetRandomValue(0, 200) < 10) {
            float x = static_cast<float>(GetRandomValue(0, screenWidth + 200));
            Color randomColor = BLUE;
            raindrops.push_back({Vector2{x, 0}, randomColor, static_cast<float>(GetRandomValue(-45, 45))});
        }
    }
}

void Rain::drawTo() {
    for (auto &raindrop : raindrops) {
        raindrop.position.x -= 4;
        raindrop.position.y += 7;

        DrawRectanglePro({raindrop.position.x, raindrop.position.y, raindropShape.width, raindropShape.height},
                         Vector2{raindropShape.width / 2, raindropShape.height / 2},
                         raindrop.rotation,
                         raindrop.color);
    }
    const float screenHeight = static_cast<float>(GetScreenHeight());


    for (auto it = raindrops.begin(); it != raindrops.end(); /* no increment here */) {
        if (it->position.y > screenHeight) {
            it = raindrops.erase(it);
        } else {
            ++it;
        }
    }
}
