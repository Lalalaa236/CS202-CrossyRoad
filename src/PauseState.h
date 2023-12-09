#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"
#include "TextureHolder.h"
#include "GameSettings.h"

class PauseState : public State
{
    private:
        State* prev;
        Texture2D* board;
        Texture2D* resumeButton;

    public:
        PauseState(State* prev);
        ~PauseState();

        void draw() override;
        void update() override;
        void handleEvents() override;
        void init() override;
        bool shouldPop() const override;
};

#endif