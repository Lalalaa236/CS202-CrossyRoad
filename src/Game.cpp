#include "Game.h"
#include "menustate.h" 
#include"State.h"
#include<iostream>


Game::Game() {
    stateStack.push(new MenuState());
}

Game::~Game() {
    // Cleanup
    while (!stateStack.empty()) {
        delete stateStack.top();
        stateStack.pop();
    }
}

void Game::run() {
    // Game loop
    while (!WindowShouldClose()) {
        
        State* currentState = stateStack.top();
        currentState->handleEvents();
        currentState->update();
        currentState->draw();
        
        
        State* nextState = currentState->getNextState();

        // Switch to the next state if needed
        if (nextState != nullptr) {
            stateStack.push(nextState);
           
        }        

    }

    CloseWindow();
}
