#include "raylib.h"

//included raymath to fix vector 2 error 
#include "raymath.h"

int main() {
const int screenWidth = 850;
 const int screenHeight = 400;

   InitWindow(screenWidth, screenHeight, "Doodle Abstract Game ");

//adding texture for the background/ cartoon effect 

   Texture2D midground = LoadTexture ("Assets_Resources/Doodle_Game.png");

  
 // Add int for moving of the ball on screen 
    float scrollingMid = 0.0f;

    float ballX = GetScreenWidth() / 2.0f;

    float ballY = GetScreenWidth() / 2.0f; 

    float ballRadius = 5; 

    float ballSpeedX = 200;

    float ballSpeedY = 200; 
  
    
// setting game to run at 60 frames -per-second 
  SetTargetFPS(60);

  //Main Game loop 

    while (!WindowShouldClose() /*WindowShouldClose returns true if esc is clicked and closes the window*/)
    {

     
      //update 

        
        scrollingMid -= 0.5f;
       
        if (scrollingMid <= -midground.width*2) scrollingMid = 0;
       

      ballX += ballSpeedX * GetFrameTime();
      ballY += ballSpeedY * GetFrameTime(); 

// reverse speed of ball 
       
       if (ballY < 0 )
     
       {

           ballY = 0;
           ballSpeedY *= -1; 


       }

// Adding screenheight so the ball can not get stuck at the bottom of the screen. 
    if (ballY > GetScreenHeight()) 
    {

         ballY =GetScreenHeight();
         ballSpeedY *= -1; 
    
    }

      //Draw 
      
      
      BeginDrawing();

     // using  layers to place code in the right place (back to front) 
      //when the window is activated (press run) it should show a moving background on the screen. 

      DrawTextureEx(midground, (Vector2){ scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
      DrawTextureEx(midground, (Vector2){ midground.width*2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);
    
     // when drawing the ball, (which will be replaced by an asset later on) in the middle of the screen and colour black. 
      DrawCircle((int) ballX, (int) ballY, ballRadius, WHITE);
  

      //drawing the rectangle  , to act as the left side paddle  for our Game, (Which will be replaced by an asset later on) colour black. 

      DrawRectangle(50, GetScreenHeight() / 2 -50, 10, 100, BLACK); 

      //drawing the Paddle for the Right side/ colour Black. 

      DrawRectangle(GetScreenWidth() -50 -10, GetScreenHeight() / 2 -50, 10, 100, BLACK); 



    
      EndDrawing();

      }

      //De-Initialization  
    //  unload background texture 
      UnloadTexture(midground);

    
  CloseWindow();
  
  return 0; 
  
}

