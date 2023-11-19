#include "raylib.h"

#include "raymath.h"

int main() {
const int screenWidth = 800;
 const int screenHeight = 500;

   InitWindow(screenWidth, screenHeight, "Fire Ball Game ");

//adding texture for the background in layers/ cartoon effect 

   Texture2D midground = LoadTexture ("Assets_Resources/platformer_background_1.png");
  
 
    float scrollingMid = 0.0f;
    
    
// setting game to run at 60 frames -per-second 
  SetTargetFPS(60);

  //Main Game loop 

    while (!WindowShouldClose() /*WindowShouldClose returns true if esc is clicked and closes the window*/)
    {

      //update 

        
        scrollingMid -= 0.5f;
       
        if (scrollingMid <= -midground.width*2) scrollingMid = 0;
       

      //Draw 
      BeginDrawing();

      ClearBackground (GetColor(0x052c46ff));

      DrawTextureEx(midground, (Vector2){ scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
      DrawTextureEx(midground, (Vector2){ midground.width*2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);

    
      EndDrawing();

      }

      //De-Initialization 
    //  unload background texture 
      UnloadTexture(midground);

    
  CloseWindow();
  
}

