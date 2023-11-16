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
        TABLE_HIGHSCORE
       
    };
}

class TextureHolder        // Singleton pattern
{
private:
    static TextureHolder gTextureHolder;
    std::map<Textures::ID, std::unique_ptr<Texture2D>> mTextureMap;
    TextureHolder();
    TextureHolder(const TextureHolder &) = delete;
    TextureHolder &operator=(const TextureHolder &) = delete;

public:
    static TextureHolder &getHolder();      
    ~TextureHolder();
    void load(Textures::ID id, const std::string &filename);
    Texture2D &get(Textures::ID id);
    const Texture2D &get(Textures::ID id) const;
};