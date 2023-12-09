#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include "raylib.h"
#include <string>

class MusicManager
{
    private:
        Music music;
        bool isSoundOn;
        float volume;
        // float curVolume;
        MusicManager();
        MusicManager(const MusicManager& other) = delete;
        MusicManager& operator=(const MusicManager& other) = delete;
    public:
        static MusicManager& getManager();
        
        ~MusicManager();

        void play();
        float getVolume() const;
        void setMusic(const std::string& path);
        bool getIsSoundOn() const;
        void toggleSound();
        void setVolume(float volume);
};

#endif