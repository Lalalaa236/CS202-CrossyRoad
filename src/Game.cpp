#include "Game.h"
#include "menustate.h" 
#include"State.h"
#include"TextureHolder.h"
#include<iostream>


Game::Game() {
    stateStack.push(new MenuState());
}

Game::~Game() {
    // Cleanup
    while (!stateStack.empty()) {
        delete stateStack.top();
        stateStack.pop();
    }
}
void Game::loadAllTexture(){
    TextureHolder::getHolder().load(Textures::CLOSE_BUTTON, "../CS202-CROSSROAD/image/general/closeButton.png");
    TextureHolder::getHolder().load(Textures::BACKGROUND_MENU, "../CS202-CROSSROAD/image/menu/bg.png");
    TextureHolder::getHolder().load(Textures::BUTTON_0, "../CS202-CROSSROAD/image/menu/about.png");
    TextureHolder::getHolder().load(Textures::BUTTON_1, "../CS202-CROSSROAD/image/menu/about.png");
    TextureHolder::getHolder().load(Textures::BUTTON_2, "../CS202-CROSSROAD/image/menu/leader.png");
    TextureHolder::getHolder().load(Textures::BUTTON_3, "../CS202-CROSSROAD/image/menu/prize.png");
    TextureHolder::getHolder().load(Textures::BUTTON_4, "../CS202-CROSSROAD/image/menu/play.png");
    TextureHolder::getHolder().load(Textures::NAME_LOGO, "../CS202-CROSSROAD/image/menu/name.png");  
    
    TextureHolder::getHolder().load(Textures::TABLE_SETTING, "../CS202-CROSSROAD/image/Setting/SettingBoard.png");
    TextureHolder::getHolder().load(Textures::SOUND_ON, "../CS202-CROSSROAD/image/Setting/sound.png");
    TextureHolder::getHolder().load(Textures::SOUND_OFF, "../CS202-CROSSROAD/image/Setting/sound_off.png");
    TextureHolder::getHolder().load(Textures::GREY_BAR, "../CS202-CROSSROAD/image/Setting/greyBar.png");
    TextureHolder::getHolder().load(Textures::GREEN_BAR, "../CS202-CROSSROAD/image/Setting/greenBar.png");
    
    TextureHolder::getHolder().load(Textures::TABLE_HIGHSCORE, "../CS202-CROSSROAD/image/highscore/highScoreBoard.png");
    TextureHolder::getHolder().load(Textures::DOT, "../CS202-CROSSROAD/image/highscore/dot.png");
    
}
void Game::run() {
    const int screenWidth = 1512;
    const int screenHeight = 982;
    InitWindow(screenWidth, screenHeight, "Crossing Road");
    SetTargetFPS(60);
    
    loadAllTexture();
    stateStack.top()->init();
    // Game loop
    InitAudioDevice();
    bgMusic = LoadMusicStream("../CS202-CROSSROAD/image/Sound/bgMusic.mp3");
    PlayMusicStream(bgMusic);
    while (!WindowShouldClose() && !stateStack.empty()) {
        UpdateMusicStream(bgMusic);
        State* currentState = stateStack.top();
        currentState->setState();
        currentState->update();
        currentState->draw();
        currentState->handleEvents();

        State* newState = currentState->getNextState();
        //std::cout <<"**" << currentState << std::endl;

        if (currentState->shouldPop()) {
            delete currentState;
            stateStack.pop();
        } 
        if (newState != nullptr) {
            //std::cout <<"*" << newState << std::endl;
            stateStack.push(newState);
        }
}
    CloseWindow();
}
