#ifndef LoseState_H
#define LoseState_H

#include "State.h"
#include "TextureHolder.h"
#include "GameSettings.h"

class LoseState : public State
{
    private:
        Texture2D* board;
        Texture2D* restartButton;
        Texture2D* quitButton;
    
        

    public:
        LoseState(StateStack& stack);
        ~LoseState();

        void draw() override;
        void update() override;
        void handleEvents() override;
};

#endif