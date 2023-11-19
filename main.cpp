#include "raylib.h"

//included raymath to fix vector 2 error 
#include "raymath.h"

int main() {
const int screenWidth = 850;
 const int screenHeight = 400;

   InitWindow(screenWidth, screenHeight, "Doodle Abstract Game ");

//adding texture for the background/ cartoon effect 

   Texture2D midground = LoadTexture ("Assets_Resources/Doodle_Game.png");

  
 
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

