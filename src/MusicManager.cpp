#include "../include/MusicManager.h"

MusicManager::MusicManager()
    : isSoundOn(true), volume(1.0f) //, curVolume(1.0f)
{
    InitAudioDevice();
    music = LoadMusicStream("image/Sound/whistle.mp3");

    SetMusicVolume(music, volume);
    PlayMusicStream(music);
}

MusicManager::~MusicManager() {
    UnloadMusicStream(music);
    CloseAudioDevice();
}

MusicManager &MusicManager::getManager() {
    static MusicManager manager;
    return manager;
}

void MusicManager::play() {
    if (isSoundOn)
        UpdateMusicStream(music);
}

float MusicManager::getVolume() const {
    return volume;
}

void MusicManager::setMusic(const std::string &path) {
    UnloadMusicStream(music);
    music = LoadMusicStream(path.c_str());
    SetMusicVolume(music, volume);
    PlayMusicStream(music);
}

bool MusicManager::getIsSoundOn() const {
    return isSoundOn;
}

void MusicManager::toggleSound() {
    isSoundOn = !isSoundOn;
    if (isSoundOn)
        SetMusicVolume(music, volume);
    else
        SetMusicVolume(music, 0.0f);
}

void MusicManager::setVolume(float volume) {
    this->volume = volume;
    SetMusicVolume(music, volume);
}