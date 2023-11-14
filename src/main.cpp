#include "Game.h"
#include"raylib.h"

using namespace std;

int main() {
    const int screenWidth = 1512;
    const int screenHeight = 982;
    InitWindow(screenWidth, screenHeight, "Crossing Road");
    SetTargetFPS(60);
    Game game;
    game.run();
	return 0;
}




