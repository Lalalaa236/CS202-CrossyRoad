#include"settingState.h"
#include"TextureHolder.h"
settingState::settingState(){
    shouldPopState = false;
}

void settingState::init(){
    // background = LoadTexture("../CS202-CROSSROAD/image/Setting/bg.png");
    // settingBoard = LoadTexture("../CS202-CROSSROAD/image/Setting/SettingBoard.png");
    // closeButton = LoadTexture("../CS202-CROSSROAD/image/Setting/closeButton.png");
    // sound[0] = LoadTexture("../CS202-CROSSROAD/image/Setting/1.png");
    // sound[1] = LoadTexture("../CS202-CROSSROAD/image/Setting/2.png");
    // sound[2] = LoadTexture("../CS202-CROSSROAD/image/Setting/3.png");
    // sound[3] = LoadTexture("../CS202-CROSSROAD/image/Setting/sound.png");
    // sound[4] = LoadTexture("../CS202-CROSSROAD/image/Setting/sound_off.png");
    background = &TextureHolder::getHolder().get(Textures::BACKGROUND_MENU);
    settingBoard =  &TextureHolder::getHolder().get(Textures::TABLE_SETTING);
    sound[0] = &TextureHolder::getHolder().get(Textures::SOUND_ON);
    sound[1] = &TextureHolder::getHolder().get(Textures::SOUND_OFF);
    sound[2] = &TextureHolder::getHolder().get(Textures::GREY_BAR);
    sound[3] = &TextureHolder::getHolder().get(Textures::GREEN_BAR);
    sound[4] = &TextureHolder::getHolder().get(Textures::DOT);
    closeButton = &TextureHolder::getHolder().get(Textures::CLOSE_BUTTON);
}
void settingState::handleEvents(){
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        Vector2 mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition,{1113,202,closeButton->width * 1.0f,closeButton->height*1.0f})){
            shouldPopState = true;  
        }
        if (CheckCollisionPointRec(mousePosition,{445,449,sound[0]->width * 1.0f,sound[1]->height*1.0f})){
            
        }
    }  
}

void settingState::update(){

}

void settingState::draw() const{
    float scaleWidth = (float)GetScreenWidth()/ background->width;
    float scaleHeight = (float)GetScreenHeight() / background->height;
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // Draw background image
    DrawTexturePro(
        *background,            
        {0, 0, float(background->width), float(background->height)}, 
        {0, 0, background->width *  scaleWidth, background->height * scaleHeight},            
        {0, 0},       
        0,                     
        WHITE                                      
    );
    DrawTexture(*settingBoard, 319, 81, WHITE);
    DrawTexture(*closeButton, 1113, 202, WHITE);  
    // if (!soundState){
    //     DrawTexture(*sound[0], 445, 449, WHITE);
    // }else{
    //     DrawTexture(*sound[1], 445, 449, WHITE);
    // }

    EndDrawing();
}

settingState::~settingState(){

}
    
bool settingState::shouldPop() const{
    return shouldPopState;
}