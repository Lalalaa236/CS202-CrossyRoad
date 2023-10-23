#include"FE.h"



void CreateMenu(const int screenW, const int screenH){
    
    const char* menuItems[] = { "Continue", "Play", "Setting", "Help", "Score Board", "Quit" };
    int itemCount = 6;
    // Load a background texture
    Texture2D background = LoadTexture("../CS202-CROSSROAD/Image/background.png");
    
    // Calculate the scale factors to fit the image to the window size
    float scaleWidth = (float)screenW / background.width;
    float scaleHeight = (float)screenH / background.height;
    
    // Create buttons
    Rectangle buttonBounds[6];
    for (int i = 0; i < itemCount; i++) {
        buttonBounds[i] = { (float) screenW / 2 - 100, (float) screenH / 2 - 30 + i * 50, 300, 40 };
    }
    //load music
    InitAudioDevice(); 
    Music music = LoadMusicStream("../CS202-CROSSROAD/Sound/background_music.mp3");
    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        // Check mouse input for button clicks
        for (int i = 0; i < itemCount; i++) {
            if (CheckCollisionPointRec(GetMousePosition(), buttonBounds[i])) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (i == 0) {
                        // "Continue" button clicked, implement the action for "Continue"
                    }
                    else if (i == 1) {
                        // "Play" button clicked, implement the action for "Play"
                    }
                    else if (i == 2) {
                        // "Setting" button clicked, implement the action for "Setting"
                    }
                    else if (i == 3) {
                        // "Help" button clicked, implement the action for "Help"
                    }
                    else if (i == 4) {
                        // "Score Board" button clicked, implement the action for "Score Board"
                    }
                    else if (i == 5) {
                        // "Quit" button clicked, implement the action for "Quit"
                        break; // Exit the game
                    }
                }
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw background image
        DrawTexturePro(
            background,            
            {0, 0, float(background.width), float(background.height)}, 
            {0, 0, background.width * scaleWidth, background.height * scaleHeight},            
            {0, 0},       
            0,                     
            WHITE                                      
        );
        
        // Draw buttons
        for (int i = 0; i < itemCount; i++) {
            if (CheckCollisionPointRec(GetMousePosition(), buttonBounds[i])) {
                DrawRectangleRec(buttonBounds[i], RED);
            } else {
                DrawRectangleRec(buttonBounds[i], DARKGRAY);
            }
            DrawText(menuItems[i], buttonBounds[i].x + 10, buttonBounds[i].y + 10, 30, WHITE);
        }

        EndDrawing();
    }
    UnloadTexture(background);
    StopMusicStream(music);
    UnloadMusicStream(music); 
    CloseWindow();
}