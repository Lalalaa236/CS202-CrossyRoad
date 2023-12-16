#include "Game.h"
#include "GameSettings.h"
#include "State.h"
#include "TextureHolder.h"
#include <iostream>

Game::Game() {
    if (GetWindowHandle())
        return;

    // Initialization for raylib
    SetTraceLogLevel(LOG_WARNING);

    // Initialization for window
    InitWindow(settings::SCREEN_WIDTH, settings::SCREEN_HEIGHT, "Crossing Road");
    SetExitKey(KEY_NULL); // Set exit key to F12
    SetTargetFPS(settings::SCREEN_FPS);
    SetWindowIcon(LoadImage("image/menu/name.png"));

    // Initialization for texture
    loadAllTexture();
    // stateStack.top()->init();

    // Initialization for audio
    // InitAudioDevice();
    // bgMusic = LoadMusicStream("image/Sound/whistle.mp3");
    // PlayMusicStream(bgMusic);
    MusicManager::getManager().setMusic("image/Sound/whistle.mp3");

    registerState();
    stateStack.pushState(States::ID::Menu);
}

Game::~Game() {
    // Cleanup
    if (!GetWindowHandle())
        return;

    CloseWindow();

    TextureHolder::getHolder().clear();
}

// void Game::toggleSound() {
//     soundEnabled = !soundEnabled;

//     if (soundEnabled) {
//         PlayMusicStream(bgMusic);
//     }
//     else {
//         StopMusicStream(bgMusic);
//     }
// }

// bool Game::getSoundState() {
//     return soundEnabled;
// }

// float Game::getVolume() {
//     return volume;
// }

// void Game::setVolume(float newVolume) {
//     this->volume = newVolume;
//     SetMusicVolume(bgMusic, volume);
// }

// void Game::setSoundState(bool ok) {
//     soundEnabled = ok;
// }

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
    TextureHolder::getHolder().load(Textures::LEADER_BOARD, "image/highscore/leaderBoard.png");

    TextureHolder::getHolder().load(Textures::INSTRUCTION_1, "image/instruction/instruction1.png");
    TextureHolder::getHolder().load(Textures::INSTRUCTION_2, "image/instruction/instruction2.png");

    TextureHolder::getHolder().load(Textures::SKIN_TABLE, "image/skin/skinBoard.png");
    TextureHolder::getHolder().load(Textures::CONFIRM_BUTTON, "image/skin/confirmButton.png");

    TextureHolder::getHolder().load(Textures::GRASS, "image/gamestate/grass.png");
    TextureHolder::getHolder().load(Textures::ROAD, "image/gamestate/line.png");

    TextureHolder::getHolder().load(Textures::RED_LIGHT, "image/gamestate/RedLight.png");
    TextureHolder::getHolder().load(Textures::YELLOW_LIGHT, "image/gamestate/YellowLight.png");
    TextureHolder::getHolder().load(Textures::GREEN_LIGHT, "image/gamestate/GreenLight.png");
    TextureHolder::getHolder().load(Textures::TRAIN_RED_LIGHT, "image/gamestate/TrainLightRed.png");
    TextureHolder::getHolder().load(Textures::TRAIN_GREEN_LIGHT, "image/gamestate/TrainLightGreen.png");

    TextureHolder::getHolder().load(Textures::SKIN_FULL, "image/skin/1/full.png"); // Place holder

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

    TextureHolder::getHolder().load(Textures::BIKE_1, "image/Bike/frame_1.png");
    TextureHolder::getHolder().load(Textures::BIKE_2, "image/Bike/frame_2.png");
    TextureHolder::getHolder().load(Textures::BIKE_3, "image/Bike/frame_3.png");
    TextureHolder::getHolder().load(Textures::BIKE_4, "image/Bike/frame_4.png");
    TextureHolder::getHolder().load(Textures::BIKE_5, "image/Bike/frame_5.png");
    TextureHolder::getHolder().load(Textures::BIKE_6, "image/Bike/frame_6.png");
    TextureHolder::getHolder().load(Textures::BIKE_7, "image/Bike/frame_7.png");
    TextureHolder::getHolder().load(Textures::BIKE_8, "image/Bike/frame_8.png");
    TextureHolder::getHolder().load(Textures::BIKE_9, "image/Bike/frame_9.png");
    TextureHolder::getHolder().load(Textures::BIKE_10, "image/Bike/frame_10.png");

    TextureHolder::getHolder().load(Textures::CAB_1, "image/Cab/frame_1.png");
    TextureHolder::getHolder().load(Textures::CAB_2, "image/Cab/frame_2.png");
    TextureHolder::getHolder().load(Textures::CAB_3, "image/Cab/frame_3.png");
    TextureHolder::getHolder().load(Textures::CAB_4, "image/Cab/frame_4.png");
    TextureHolder::getHolder().load(Textures::CAB_5, "image/Cab/frame_5.png");

    TextureHolder::getHolder().load(Textures::CAR_1, "image/Car/frame_1.png");
    TextureHolder::getHolder().load(Textures::CAR_2, "image/Car/frame_2.png");
    TextureHolder::getHolder().load(Textures::CAR_3, "image/Car/frame_3.png");
    TextureHolder::getHolder().load(Textures::CAR_4, "image/Car/frame_4.png");
    TextureHolder::getHolder().load(Textures::CAR_5, "image/Car/frame_5.png");

    TextureHolder::getHolder().load(Textures::TRUCK_1, "image/Truck/frame_1.png");
    TextureHolder::getHolder().load(Textures::TRUCK_2, "image/Truck/frame_2.png");
    TextureHolder::getHolder().load(Textures::TRUCK_3, "image/Truck/frame_3.png");
    TextureHolder::getHolder().load(Textures::TRUCK_4, "image/Truck/frame_4.png");
    TextureHolder::getHolder().load(Textures::TRUCK_5, "image/Truck/frame_5.png");

    TextureHolder::getHolder().load(Textures::TAXI_1, "image/Taxi/frame_1.png");
    TextureHolder::getHolder().load(Textures::TAXI_2, "image/Taxi/frame_2.png");
    TextureHolder::getHolder().load(Textures::TAXI_3, "image/Taxi/frame_3.png");
    TextureHolder::getHolder().load(Textures::TAXI_4, "image/Taxi/frame_4.png");
    TextureHolder::getHolder().load(Textures::TAXI_5, "image/Taxi/frame_5.png");

    TextureHolder::getHolder().load(Textures::SKIN_1, "image/skin/1/full.png");
    TextureHolder::getHolder().load(Textures::SKIN_2, "image/skin/2/full.png");

    TextureHolder::getHolder().load(Textures::PAUSE_BUTTON, "image/gameState/Pause.png");

    TextureHolder::getHolder().load(Textures::PAUSE_BOARD, "image/PauseGame/board.png");
    TextureHolder::getHolder().load(Textures::RESUME_BUTTON, "image/PauseGame/playbtn.png");
    TextureHolder::getHolder().load(Textures::RESTART_BUTTON, "image/PauseGame/restartbtn.png");
    TextureHolder::getHolder().load(Textures::QUIT_BUTTON, "image/PauseGame/homebtn.png");
    TextureHolder::getHolder().load(Textures::SAVE_BUTTON, "image/PauseGame/savebtn.png");
    TextureHolder::getHolder().load(Textures::TIMER_1, "image/PauseGame/1.png");
    TextureHolder::getHolder().load(Textures::TIMER_2, "image/PauseGame/2.png");
    TextureHolder::getHolder().load(Textures::TIMER_3, "image/PauseGame/3.png");

    TextureHolder::getHolder().load(Textures::RAILWAY, "image/gameState/railway.png");
    TextureHolder::getHolder().load(Textures::TRAIN_RIGHT, "image/train/Right.png");

    TextureHolder::getHolder().load(Textures::LOSE_BOARD, "image/LoseGame/Board.png");
}

void Game::run() {
    while (!WindowShouldClose()) {
        // UpdateMusicStream(bgMusic);
        MusicManager::getManager().play();

        stateStack.update();
        stateStack.draw();
        stateStack.handleEvents();
    }
}

void Game::registerState() {
    stateStack.registerState<MenuState>(States::ID::Menu);
    stateStack.registerState<GameState>(States::ID::Game);
    stateStack.registerState<PauseState>(States::ID::Pause);
    stateStack.registerState<settingState>(States::ID::Settings);
    stateStack.registerState<InstructionState>(States::ID::Instructions);
    stateStack.registerState<highScoreState>(States::ID::Highscore);
    stateStack.registerState<SkinState>(States::ID::Skin);
    stateStack.registerState<LoseState>(States::ID::GameOver);
    stateStack.registerState<SaveState>(States::ID::Save);
    stateStack.registerState<LoadState>(States::ID::Load);
}