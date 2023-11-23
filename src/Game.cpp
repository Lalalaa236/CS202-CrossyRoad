#include "Game.h"
#include "menustate.h" 
#include "State.h"
#include"TextureHolder.h"
#include <iostream>


Game::Game() {
    if (GetWindowHandle())
        return;
    stateStack.push(new MenuState(*this));
    soundEnabled = true;
    volume = 1.0f;

    const int screenWidth = 1512;
    const int screenHeight = 982;

    InitWindow(screenWidth, screenHeight, "Crossing Road");
    SetTargetFPS(60);
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
}

void Game::run() {
    while (!WindowShouldClose() && !stateStack.empty()) {
        UpdateMusicStream(bgMusic);
        State* currentState = stateStack.top();
        currentState->setState();
        currentState->handleEvents();
        currentState->update();
        currentState->draw();

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
