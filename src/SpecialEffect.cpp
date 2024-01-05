#include "SpecialEffect.h"
#include "MusicManager.h"
#include <algorithm>

SpecialEffect::SpecialEffect() {
    isToggleSound = false;
    particleShape.width = 4;
    particleShape.height = 7;
    state = 0;
}

void SpecialEffect::setState(int st) {
    state = st;
     if (state == 1) {
        PlaySound(effectSound);
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
        StopSound(effectSound);
    }
}

int SpecialEffect::getState() {
    return state;
}
