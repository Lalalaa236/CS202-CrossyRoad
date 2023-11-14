#include"settingState.h"

settingState::settingState(){
    background = LoadTexture("../CS202-CROSSROAD/image/Setting/bg.png");
    settingBoard = LoadTexture("../CS202-CROSSROAD/image/Setting/SettingBoard.png");
    closeButton = LoadTexture("../CS202-CROSSROAD/image/Setting/closeButton.png");
    shouldPopState = false;
}

void settingState::handleEvents(){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition,{1113,202,closeButton.width * 1.0f,closeButton.height*1.0f})){
            shouldPopState = true;  
        }
    }  
}

void settingState::update(){

}

void settingState::draw() const{
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
    DrawTexture(settingBoard, 319, 81, WHITE);
    DrawTexture(closeButton, 1113, 202, WHITE);  

    EndDrawing();
}

settingState::~settingState(){

}
    
bool settingState::shouldPop() const{
    return shouldPopState;
}