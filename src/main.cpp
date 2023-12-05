#include "Game.h"
#include "raylib.h"
#include <vector>
using namespace std;

#include <chrono>
#include <thread>

int main() {
    Game* game = new Game();
    game->run();

    delete game;
    return 0;
}