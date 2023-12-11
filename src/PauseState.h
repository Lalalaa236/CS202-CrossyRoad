#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"
#include "TextureHolder.h"
#include "GameSettings.h"

class PauseState : public State
{
    private:
        float timerCount;
        Texture2D* board;
        Texture2D* resumeButton;
        Texture2D* restartButton;
        Texture2D* quitButton;
        Texture2D* saveButton;
        Texture2D* timer;

    public:
        PauseState(StateStack& stack);
        ~PauseState();

        void draw() override;
        void update() override;
        void handleEvents() override;
};

#endif