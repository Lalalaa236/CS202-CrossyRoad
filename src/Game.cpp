#include "Game.h"
#include "menustate.h" 
#include "State.h"
#include"TextureHolder.h"
#include <iostream>
#include "GameSettings.h"  


Game::Game() {
    if (GetWindowHandle())
        return;
    stateStack.push(new MenuState(*this));
    soundEnabled = true;
    volume = 1.0f;

    InitWindow(settings::SCREEN_WIDTH, settings::SCREEN_HEIGHT, "Crossing Road");
    SetTargetFPS(settings::SCREEN_FPS);
    loadAllTexture();
    stateStack.top()->init();

    InitAudioDevice();
    bgMusic = LoadMusicStream("image/Sound/bgMusic.mp3");
    PlayMusicStream(bgMusic);
}

Game::~Game() {
    // Cleanup
    if (!GetWindowHandle())
        return;

    CloseWindow();

    while (!stateStack.empty()) {
        delete stateStack.top();
        stateStack.pop();
    }

    UnloadMusicStream(bgMusic);
    CloseAudioDevice();
}

void Game::toggleSound() {
    soundEnabled = !soundEnabled;

    if (soundEnabled) {
        PlayMusicStream(bgMusic);
    }
    else {
        StopMusicStream(bgMusic);
    }
}

bool Game::getSoundState() {
    return soundEnabled;
}

float Game::getVolume() {
    return volume;
}

void Game::setVolume(float newVolume) {
    this->volume = newVolume;
    SetMusicVolume(bgMusic, volume);
}

void Game::setSoundState(bool ok) {
    soundEnabled = ok;
}

void Game::loadAllTexture() {
    TextureHolder::getHolder().load(Textures::CLOSE_BUTTON, "image/general/closeButton.png");
    TextureHolder::getHolder().load(Textures::NEXT_BUTTON, "image/general/nextButton.png");
    TextureHolder::getHolder().load(Textures::PREVIOUS_BUTTON, "image/general/previousButton.png");


    TextureHolder::getHolder().load(Textures::BACKGROUND_MENU, "image/menu/bg.png");
    TextureHolder::getHolder().load(Textures::BUTTON_0, "image/menu/about.png");
    TextureHolder::getHolder().load(Textures::BUTTON_1, "image/menu/setting.png");
    TextureHolder::getHolder().load(Textures::BUTTON_2, "image/menu/leader.png");
    TextureHolder::getHolder().load(Textures::BUTTON_3, "image/menu/prize.png");
    TextureHolder::getHolder().load(Textures::BUTTON_4, "image/menu/play.png");
    TextureHolder::getHolder().load(Textures::NAME_LOGO, "image/menu/name.png");

    TextureHolder::getHolder().load(Textures::TABLE_SETTING, "image/Setting/SettingBoard.png");
    TextureHolder::getHolder().load(Textures::SOUND_ON, "image/Setting/sound.png");
    TextureHolder::getHolder().load(Textures::SOUND_OFF, "image/Setting/sound_off.png");
    TextureHolder::getHolder().load(Textures::GREY_BAR, "image/Setting/greyBar.png");
    TextureHolder::getHolder().load(Textures::GREEN_BAR, "image/Setting/greenBar.png");
    TextureHolder::getHolder().load(Textures::DOT, "image/Setting/dot.png");

    TextureHolder::getHolder().load(Textures::TABLE_HIGHSCORE, "image/highscore/highScoreBoard.png");

    TextureHolder::getHolder().load(Textures::INSTRUCTION_1, "image/instruction/instruction1.png");
    TextureHolder::getHolder().load(Textures::INSTRUCTION_2, "image/instruction/instruction2.png");

    TextureHolder::getHolder().load(Textures::SKIN_TABLE, "image/skin/skinBoard.png");
    TextureHolder::getHolder().load(Textures::CONFIRM_BUTTON, "image/skin/confirmButton.png");

    TextureHolder::getHolder().load(Textures::GRASS, "image/gamestate/grass.png");
    TextureHolder::getHolder().load(Textures::ROAD, "image/gamestate/line.png");

    TextureHolder::getHolder().load(Textures::RED_LIGHT, "image/gamestate/RedLight.png");
    TextureHolder::getHolder().load(Textures::YELLOW_LIGHT, "image/gamestate/YellowLight.png");
    TextureHolder::getHolder().load(Textures::GREEN_LIGHT, "image/gamestate/GreenLight.png");

    TextureHolder::getHolder().load(Textures::BIRD_1, "image/Bird/frame_1.png");
    TextureHolder::getHolder().load(Textures::BIRD_2, "image/Bird/frame_2.png");
    TextureHolder::getHolder().load(Textures::BIRD_3, "image/Bird/frame_3.png");
    TextureHolder::getHolder().load(Textures::BIRD_4, "image/Bird/frame_4.png");
    TextureHolder::getHolder().load(Textures::BIRD_5, "image/Bird/frame_5.png");
    TextureHolder::getHolder().load(Textures::BIRD_6, "image/Bird/frame_6.png");
    TextureHolder::getHolder().load(Textures::BIRD_7, "image/Bird/frame_7.png");
    TextureHolder::getHolder().load(Textures::BIRD_8, "image/Bird/frame_8.png");

    TextureHolder::getHolder().load(Textures::CAT_1, "image/Cat/frame-1.png");
    TextureHolder::getHolder().load(Textures::CAT_2, "image/Cat/frame-2.png");
    TextureHolder::getHolder().load(Textures::CAT_3, "image/Cat/frame-3.png");
    TextureHolder::getHolder().load(Textures::CAT_4, "image/Cat/frame-4.png");
    TextureHolder::getHolder().load(Textures::CAT_5, "image/Cat/frame-5.png");
    TextureHolder::getHolder().load(Textures::CAT_6, "image/Cat/frame-6.png");
    TextureHolder::getHolder().load(Textures::CAT_7, "image/Cat/frame-7.png");
    TextureHolder::getHolder().load(Textures::CAT_8, "image/Cat/frame-8.png");

    TextureHolder::getHolder().load(Textures::DOG_1, "image/Dog/frame-1.png");
    TextureHolder::getHolder().load(Textures::DOG_2, "image/Dog/frame-2.png");
    TextureHolder::getHolder().load(Textures::DOG_3, "image/Dog/frame-3.png");
    TextureHolder::getHolder().load(Textures::DOG_4, "image/Dog/frame-4.png");
    TextureHolder::getHolder().load(Textures::DOG_5, "image/Dog/frame-5.png");
    TextureHolder::getHolder().load(Textures::DOG_6, "image/Dog/frame-6.png");
    TextureHolder::getHolder().load(Textures::DOG_7, "image/Dog/frame-7.png");
    TextureHolder::getHolder().load(Textures::DOG_8, "image/Dog/frame-8.png");
    TextureHolder::getHolder().load(Textures::DOG_9, "image/Dog/frame-9.png");
    TextureHolder::getHolder().load(Textures::DOG_10, "image/Dog/frame-10.png");
    TextureHolder::getHolder().load(Textures::DOG_11, "image/Dog/frame-11.png");
    TextureHolder::getHolder().load(Textures::DOG_12, "image/Dog/frame-12.png");
    TextureHolder::getHolder().load(Textures::DOG_13, "image/Dog/frame-13.png");
    TextureHolder::getHolder().load(Textures::DOG_14, "image/Dog/frame-14.png");
    TextureHolder::getHolder().load(Textures::DOG_15, "image/Dog/frame-15.png");
    TextureHolder::getHolder().load(Textures::DOG_16, "image/Dog/frame-16.png");
    TextureHolder::getHolder().load(Textures::DOG_17, "image/Dog/frame-17.png");
    TextureHolder::getHolder().load(Textures::DOG_18, "image/Dog/frame-18.png");
    TextureHolder::getHolder().load(Textures::DOG_19, "image/Dog/frame-19.png");
    TextureHolder::getHolder().load(Textures::DOG_20, "image/Dog/frame-20.png");

    TextureHolder::getHolder().load(Textures::TIGER_1, "image/Tiger/frame-1.png");
    TextureHolder::getHolder().load(Textures::TIGER_2, "image/Tiger/frame-2.png");
    TextureHolder::getHolder().load(Textures::TIGER_3, "image/Tiger/frame-3.png");
    TextureHolder::getHolder().load(Textures::TIGER_4, "image/Tiger/frame-4.png");
    TextureHolder::getHolder().load(Textures::TIGER_5, "image/Tiger/frame-5.png");
    TextureHolder::getHolder().load(Textures::TIGER_6, "image/Tiger/frame-6.png");


    TextureHolder::getHolder().load(Textures::RABBIT_1, "image/Rabbit/frame-1.png");
    TextureHolder::getHolder().load(Textures::RABBIT_2, "image/Rabbit/frame-2.png");
    TextureHolder::getHolder().load(Textures::RABBIT_3, "image/Rabbit/frame-3.png");
    TextureHolder::getHolder().load(Textures::RABBIT_4, "image/Rabbit/frame-4.png");
    TextureHolder::getHolder().load(Textures::RABBIT_5, "image/Rabbit/frame-5.png");
    TextureHolder::getHolder().load(Textures::RABBIT_6, "image/Rabbit/frame-6.png");

    TextureHolder::getHolder().load(Textures::SKIN_1_UP, "image/skin/1/up/sprite.png");
    TextureHolder::getHolder().load(Textures::SKIN_1_DOWN, "image/skin/1/down/sprite.png");
    TextureHolder::getHolder().load(Textures::SKIN_2_UP, "image/skin/2/up/sprite.png");
    TextureHolder::getHolder().load(Textures::SKIN_2_DOWN, "image/skin/2/down/sprite.png");
}

void Game::run() {
    while (!WindowShouldClose() && !stateStack.empty()) {
        UpdateMusicStream(bgMusic);
        State* currentState = stateStack.top();
        currentState->setState();
        currentState->draw();
        currentState->update();
        currentState->handleEvents();

        State* newState = currentState->getNextState();

        if (currentState->shouldPop()) {
            delete currentState;
            stateStack.pop();
        }
        if (newState != nullptr) {

            stateStack.push(newState);
        }
    }
}
