#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.h"
#include "TextureHolder.h"

class PauseState : public State
{
    private:
        Texture2D* board;
        Texture2D* resumeButton;

    public:
        PauseState();
        ~PauseState();

        void draw() override;
        void update() override;
        void handleEvents() override;
        void init() override;
        bool shouldPop() const override;
};

#endif