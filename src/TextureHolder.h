#pragma once
#include "raylib.h"
#include <map>
#include <string>
#include <memory>
#include <stdexcept>

namespace Textures
{
    enum ID
    {
        //general 
        CLOSE_BUTTON,
        NEXT_BUTTON,
        PREVIOUS_BUTTON,

        //Menu
        BACKGROUND_MENU,
        BUTTON_0,
        BUTTON_1,
        BUTTON_2,
        BUTTON_3,
        BUTTON_4,
        NAME_LOGO,

        //setting
        TABLE_SETTING,
        SOUND_ON,
        SOUND_OFF,
        GREY_BAR,
        GREEN_BAR,
        DOT,

        //high score
        TABLE_HIGHSCORE,

        // Inscruction
        INSTRUCTION_1,
        INSTRUCTION_2,

        // Lanes
        GRASS,
        ROAD,

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

        //Tiger
        TIGER_1,
        TIGER_2,
        TIGER_3,
        TIGER_4,
        TIGER_5,
        TIGER_6,
        
        //RabBit
        RABBIT_1,
        RABBIT_2,
        RABBIT_3,
        RABBIT_4,
        RABBIT_5,
        RABBIT_6,

        //Bike
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
        BIKE_11,
        BIKE_12,
        BIKE_13,
        BIKE_14,
        BIKE_15,
        BIKE_16,
        BIKE_17,
        BIKE_18,
        BIKE_19,
        BIKE_20,
        BIKE_21,
        BIKE_22,
        BIKE_23,
        BIKE_24,
        BIKE_25,
        BIKE_26,

        //Cab
        CAB_1,
        CAB_2,
        CAB_3,
        CAB_4,
        CAB_5,
        CAB_6,
        CAB_7,
        CAB_8,
        CAB_9,
        CAB_10,
        CAB_11,
        CAB_12,
        CAB_13,
        CAB_14,
        CAB_15,
        CAB_16,
        CAB_17,
        CAB_18,
        CAB_19,
        CAB_20,
        CAB_21,

        //Car
        CAR_1,
        CAR_2,
        CAR_3,
        CAR_4,
        CAR_5,
        CAR_6,
        CAR_7,
        CAR_8,
        CAR_9,
        CAR_10,
        CAR_11,
        CAR_12,
        CAR_13,
        CAR_14,
        CAR_15,
        CAR_16,
        CAR_17,
        CAR_18,
        CAR_19,
        CAR_20,
        CAR_21,
        CAR_22,
        CAR_23,
        CAR_24,
        CAR_25,

        //Taxi
        TAXI_1,
        TAXI_2,
        TAXI_3,
        TAXI_4,
        TAXI_5,

        //Truck
        TRUCK_1,
        TRUCK_2,
        TRUCK_3,
        TRUCK_4,
        TRUCK_5,
        TRUCK_6,
        TRUCK_7,
        TRUCK_8,
        TRUCK_9,
        TRUCK_10,
        TRUCK_11,
        TRUCK_12,
        TRUCK_13,
        TRUCK_14,
        TRUCK_15,
        TRUCK_16,

    };
}

class TextureHolder        // Singleton pattern
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
};