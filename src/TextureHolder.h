#pragma once
#include "raylib.h"
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

namespace Textures {
    enum ID {
        // general
        CLOSE_BUTTON,
        NEXT_BUTTON,
        PREVIOUS_BUTTON,

        // Menu
        BACKGROUND_MENU,
        BUTTON_0,
        BUTTON_1,
        BUTTON_2,
        BUTTON_3,
        BUTTON_4,
        NAME_LOGO,

        // setting
        TABLE_SETTING,
        SOUND_ON,
        SOUND_OFF,
        GREY_BAR,
        GREEN_BAR,
        DOT,

        // high score
        TABLE_HIGHSCORE,
        LEADER_BOARD,

        // Inscruction
        INSTRUCTION_1,
        INSTRUCTION_2,

        // skin
        SKIN_TABLE,
        CONFIRM_BUTTON,

        // Lanes
        GRASS,
        ROAD,
        RAILWAY,

        // Lights
        RED_LIGHT,
        YELLOW_LIGHT,
        GREEN_LIGHT,

        //Bird
        BIRD_1,
        BIRD_2,
        BIRD_3,
        BIRD_4,
        BIRD_5,
        BIRD_6,
        BIRD_7,
        BIRD_8,

        //cat
        CAT_1,
        CAT_2,
        CAT_3,
        CAT_4,
        CAT_5,
        CAT_6,
        CAT_7,
        CAT_8,

        //dog
        DOG_1,
        DOG_2,
        DOG_3,
        DOG_4,
        DOG_5,
        DOG_6,
        DOG_7,
        DOG_8,
        DOG_9,
        DOG_10,
        DOG_11,
        DOG_12,
        DOG_13,
        DOG_14,
        DOG_15,
        DOG_16,
        DOG_17,
        DOG_18,
        DOG_19,
        DOG_20,
        DOG_21,

        // Skin
        SKIN_FULL,
        SKIN_1,
        SKIN_2,

        //Tiger
        TIGER_1,
        TIGER_2,
        TIGER_3,
        TIGER_4,
        TIGER_5,
        TIGER_6,

        //Rabbit
        RABBIT_1,
        RABBIT_2,
        RABBIT_3,
        RABBIT_4,
        RABBIT_5,
        RABBIT_6,

        //Vehicle
        BIKE_1,
        BIKE_2,
        BIKE_3,
        BIKE_4,
        BIKE_5,
        BIKE_6,
        BIKE_7,
        BIKE_8,
        BIKE_9,
        BIKE_10,

        //Cab
        CAB_1,
        CAB_2,
        CAB_3,
        CAB_4,
        CAB_5,

        //Car
        CAR_1,
        CAR_2,
        CAR_3,
        CAR_4,
        CAR_5,

        //truck
        TRUCK_1,
        TRUCK_2,
        TRUCK_3,
        TRUCK_4,
        TRUCK_5,

        //taxi
        TAXI_1,
        TAXI_2,
        TAXI_3,
        TAXI_4,
        TAXI_5,

        // Game state
        PAUSE_BUTTON,

        // Pause state
        PAUSE_BOARD,
        RESUME_BUTTON,
        QUIT_BUTTON,
        RESTART_BUTTON,
        SAVE_BUTTON,
        LOSE_BOARD,

        TIMER_1,
        TIMER_2,
        TIMER_3,

        TRAIN_LEFT,
        TRAIN_RIGHT,



    };
};

class TextureHolder // Singleton pattern
{
private:
    static TextureHolder gTextureHolder;
    std::map<Textures::ID, std::unique_ptr<Texture2D>> mTextureMap;
    TextureHolder();
    TextureHolder(const TextureHolder&) = delete;
    TextureHolder& operator=(const TextureHolder&) = delete;

public:
    static TextureHolder& getHolder();
    ~TextureHolder();

    void load(Textures::ID id, const std::string& filename);
    Texture2D& get(Textures::ID id);
    const Texture2D& get(Textures::ID id) const;

    Texture2D& operator[](Textures::ID id);
    const Texture2D& operator[](Textures::ID id) const;

    void clear();
};