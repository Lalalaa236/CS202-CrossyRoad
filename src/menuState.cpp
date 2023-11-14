#include "menuState.h"
#include "gamestate.h"  
#include"settingState.h"
#include"raylib.h"
#include<utility>


MenuState::MenuState() {
        background = LoadTexture("../CS202-CROSSROAD/image/menu/bg.png");
        button[0] = LoadTexture("../CS202-CROSSROAD/image/menu/about.png");
        button[1] = LoadTexture("../CS202-CROSSROAD/image/menu/setting.png");
        button[2] = LoadTexture("../CS202-CROSSROAD/image/menu/leader.png");
        button[3] = LoadTexture("../CS202-CROSSROAD/image/menu/prize.png");
        button[4] = LoadTexture("../CS202-CROSSROAD/image/menu/play.png");
        name = LoadTexture("../CS202-CROSSROAD/image/menu/name.png");  
        shouldPopState = false;
}   


void MenuState::handleEvents() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Get mouse position
                Vector2 mousePosition = GetMousePosition();

                Vector2 a[6]={{33,24},{1352,28},{63,802},{1352,804},{660,647},{244,191}};
        
                for (int i = 0; i < 5; i++){
                        if (CheckCollisionPointRec(mousePosition,{a[i].x,a[i].y,button[i].width * 0.3f, button[i].height * 0.3f})){
                                switch(i){
                                case 0:
                                //         //nextState = new instruction();
                                        //shouldPo
                                        break;
                                case 1:
                                        nextState = new settingState();
                                        break;
                                // case 2:
                                //         break;
                                // case 3:
                                //         break;
                                // case 4:
                                //         break;
                                // case 5:
                                //         break;
                                // default:
                                //         break;
                                 }
                        }
                }
                if (CheckCollisionPointRec(mousePosition,{a[5].x,a[5].y,name.width * 1.0f,name.height*1.0f})){
                
                }
                
        }
        
}

void MenuState::update() {
    // Update logic for the menu state
}

void MenuState::draw() const {
     
        float scaleWidth = (float)GetScreenWidth()/ background.width;
        float scaleHeight = (float)GetScreenHeight() / background.height;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw background image
        DrawTexturePro(
            background,            
            {0, 0, float(background.width), float(background.height)}, 
            {0, 0, background.width *  scaleWidth, background.height * scaleHeight},            
            {0, 0},       
            0,                     
            WHITE                                      
        );
        Vector2 a[5]={{33,24},{1352,28},{63,802},{1352,804},{660,647}};
        for (int i = 0; i < 5; i++)
        DrawTextureEx(button[i],
                      a[i],  // Position
                      0,                   // Rotation angle
                      0.3,               // Scale
                      WHITE);              // Tint color
        DrawTexture(name, 244, 191, WHITE);

        EndDrawing();

}


bool MenuState::shouldPop() const {
        return shouldPopState;
}

MenuState::~MenuState() {
        if (nextState != nullptr){
                delete nextState;
        }
        nextState = nullptr;
}
