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
    while (!WindowShouldClose() && !stateStack.empty()) {
    State* currentState = stateStack.top();
    currentState->setState();
    currentState->update();
    currentState->draw();
    currentState->handleEvents();

    State* newState = currentState->getNextState();
    //std::cout <<"**" << currentState << std::endl;

    if (currentState->shouldPop()) {
        delete currentState;
        stateStack.pop();
    } 
    if (newState != nullptr) {
        //std::cout <<"*" << newState << std::endl;
        stateStack.push(newState);
    }
}
    CloseWindow();
}
