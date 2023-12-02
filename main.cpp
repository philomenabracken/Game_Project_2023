#include "raylib.h"

//included raymath to fix vector 2 error 
#include "raymath.h"


//creating a struct to place my varuables into/ call all at once 

 struct Ball 
{
    float x, y;
    float speedX, speedY; 
    float radius; 

// creating a draw function inside the ball struct. 
      void Draw()
      {
          DrawCircle((int) x, (int) y, radius, PINK);
      
      }

};
//creating a struct for my paddles 
struct Paddle  
{

float x, y;
//only need 1 speed as its only going to move in one direction for now. 
float speed; 
// width and height of paddles 
float width, height; 

  Rectangle GetRect()
{
  return Rectangle{ x - width/ 2, y-height /2 , 10, 100};

  
}

//creating a draw function for the paddles 

void Draw()
{
   DrawRectangleRec(GetRect(), PINK); 
}

};

int main() {
const int screenWidth = 600;
 const int screenHeight = 400;  

   InitWindow(screenWidth, screenHeight, "Pink ping Pong  ");

   //game time start of 30 seconds 
   
   double starTime = GetTime();
   
   // 30 seconds 

   double duration = 30.0; 

   //background changes ever 10 seconds 

   double backgroundChangeTime = 10.0; 
  

//adding texture for the background/ cartoon effect /for each leve 1,2,3 

   Texture2D background1 = LoadTexture ("Assets_Resources/Background.png");

   Texture2D background2 =LoadTexture ("Assets_Resources/level one.png"):

 

   //Add Audio to game // learned in Class 

   InitAudioDevice();

   Sound sound = LoadSound ("SoundEffects/ballsoundmp3"); 

   Sound winner = LoadSound ("SoundEffects/crowd .mp3 ");

  
 // Add int for moving of the ball on screen   

    float scrollingMid = 0.0f;

//creating a ball struct, to hold all of the properities of the ball 
   
    Ball ball;

    ball. x = GetScreenWidth() / 2.0f;

    ball. y = GetScreenWidth() / 2.0f; 

    ball.radius = 5; 

    ball.speedX = 300;

    ball. speedY = 200; 

    //creating left paddle, with its properties, that I created at the beginning. 

    Paddle leftPaddle; 

    leftPaddle.x = 50;

    leftPaddle.y = GetScreenHeight() / 2;

    leftPaddle.width= 10; 

    leftPaddle. height = 100;

    leftPaddle.speed = 400; 

    //creating right paddle, with its proerties, that I created at the beginning. 

    Paddle rightPaddle; 

    rightPaddle. x = GetScreenWidth() - 50; 

    rightPaddle.y = GetScreenHeight() / 2;

    rightPaddle.width = 10; 

    rightPaddle. height = 100; 

    rightPaddle.speed = 500; 

    //creating A TEXT for message to appear when ball goes out. for the winner .. From class lecturere 3, time: 50:14

    const char* winnerText = nullptr;

  // creating a Timer for Game 


  
    
// setting game to run at 60 frames -per-second 
  SetTargetFPS(60);

  //Main Game loop 

    while (!WindowShouldClose() /*WindowShouldClose returns true if esc is clicked and closes the window*/)
    {

     
      //update Draw background //from class lecture 

      double currentTime = GetTime();
      double elapsedTime= currentTime -startTime; 

      if(elapsedTime >=10.0 &&! changebackground)

      {
        UnloadTexture ("background1");
        background2 = LoadTexture ("background2.png");
        changeBackground =true; 
      }

    
  
   // movement /speed   

      ball. x += ball.speedX * GetFrameTime();
      ball. y += ball. speedY * GetFrameTime(); 

// reverse speed of ball 
       
       if (ball. y < 0 )
     
       {

           ball. y = 0;
           ball. speedY*= -1; 


       }

// Adding screenheight so the ball can not get stuck at the bottom of the screen. 
    if (ball. y > GetScreenHeight()) 
    {

         ball. y =GetScreenHeight(); 
         ball. speedY *= -1; 
    

   
    // if key is pressed on key board the paddle with move up and down 
    }

    if (IsKeyDown(KEY_A))  
    {
      leftPaddle.y -= leftPaddle.speed * GetFrameTime (); 
    
    } 

    if (IsKeyDown(KEY_X))
    {
    leftPaddle.y += leftPaddle. speed * GetFrameTime();

    }
      
     // if key is pressed on key board the paddle with move up and down 

      if(IsKeyDown(KEY_P))
      
       {
       
       rightPaddle.y -= rightPaddle. speed * GetFrameTime();


      }

      if (IsKeyDown(KEY_M))
       {

        rightPaddle.y += rightPaddle.speed * GetFrameTime();


      }

      //if ball collision ito the right paddle it will bounce off  

     if (CheckCollisionCircleRec (Vector2{ball.x, ball.y}, ball .radius, rightPaddle.GetRect()))

     // To bounce the ball/ Adding the ball speed. 
     // making the ball speed up each frame 
    {

     
     if(ball.speedX > 0 )
     
      {
       ball.speedX *= -1.2f; 
       ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height /2 ) * - ball.speedX; 
      

     }

    }
     
  
      // if collision with left paddle it will bounce off 

     if (CheckCollisionCircleRec (Vector2{ball.x, ball.y}, ball .radius, leftPaddle.GetRect()))

     // To bounce the ball/ Adding the ball speed. 

    {

       if(ball.speedX < 0)

      {
       ball.speedX *= -1.2f; 
        ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle. height/2 )* ball.speedX ; 

      }
      
      {
      // if ball goes off the left side, right is the winner 

      if (ball.x < 0)
      {

        winnerText ="Right Player Wins!";

      }
      if (ball.x > GetScreenWidth()) 
      {
        
        winnerText = "Left Player Wins!";

      }
       // when game is finish can be reset by pressing space bar key 
      if (winnerText && IsKeyPressed (KEY_SPACE))
   
       {

         ball.y = GetScreenWidth() / 2;  
         ball.y = GetScreenHeight() / 2; 
         ball.speedX = 300;
         ball.speedY = 300; 
         winnerText = nullptr;  
      }
         
         if (IsKeyPressed(KEY_A))
         
         {
              PlaySound(sound);

         }


        if (IsKeyPressed(KEY_P))

        {

          PlaySound(sound); 

        }

         // if ball goes off the left side, play sound  

         if (ball.x < 0)
      {

        PlaySound  (winner);

      }

         if (ball.x > GetScreenWidth()) 
      {
        
        PlaySound  (winner);

      }



      }       
         

    }
     


      //Draw 
      
      
      BeginDrawing();

     // using  layers to place code in the right place (back to front) 
      //when the window is activated (press run) it should show a moving background on the screen. 

      ClearBackground(RAYWHITE);
      
      if (!changeBackground)
      {
        DrawTexture (background1,0,0, WHITE);
      
      }
      else 
      {
        DrawTexture(background2,0,0, WHITE)
      }
    
     // when drawing the ball, will now draw form the ball struct. 
     ball.Draw();
  

      //drawing the rectangle  , to act as the left side paddle  for our Game, (Which will be replaced by an asset later on) colour black. 

     leftPaddle.Draw();

      //drawing the Paddle for the Right side/ colour Black. 

      rightPaddle.Draw();


      //draw function for winner text 

      if (winnerText)
    
        
       // will draw text onto centre of screen 
      {
        int textWidth = MeasureText (winnerText, 60 );
        DrawText (winnerText, GetScreenWidth () / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, PINK );
      }

    
      EndDrawing();

      }

      //De-Initialization  
    //  unload background texture 
      UnloadTexture(background1);
      UnloadTexture(background2);
      UnloadSound(sound);
      UnloadSound(winner);

    CloseAudioDevice ();
  CloseWindow();
  
  return 0; 
  
}

