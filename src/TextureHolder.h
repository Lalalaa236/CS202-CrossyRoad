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