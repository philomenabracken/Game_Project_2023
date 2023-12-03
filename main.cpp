#include "raylib.h"


//Lecture two: Data Types, floats and double, slide 9 - slide 15 time: 16:01- 21:49
//turtoails online 

struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int) x, (int) y, radius, PINK);
	}
};

struct Paddle
{
	float x, y;
	float speed;
	float width, height;

  //Lecture two: Drawing objects onto screen (in my objects it was ball and retangles) time 1:04:16 - 1:07:32

	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), PINK);
	}
};

int main() {
    // Determin the Game Window Width and Height. Lecture one. time 22:32 - 37:38
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int fps= 60;
	const int backgroundChangeTime = 10* fps;

    // Initialize the Window Lecture one: Set up and screen height and width, time 22:32 - 37:38
    InitWindow(screenWidth, screenHeight, "Paddle Crash ");

    //adding texture for the background/ cartoon effect /class lexcture/ Lexture three: Loading Textures time 20:44 - 32:32

   Texture2D background1 = LoadTexture ("Assets_Resources/level one.png");

   Texture2D background2 = LoadTexture ("Assets_Resources/level two.png");

   Texture2D background3 = LoadTexture ("Assets_Resources/ level three.png");

    // Setting the Frames Per Second / lecture one 
    SetTargetFPS(60);



   // adding in frame count for background that will be displayed and number of frames that have passed for game backgrounds 
   //Lexture three: Using if statements/ true and fale time 2:30-3:42 / time 35:41 - 39:32
   
   int frameCount = 0;
   int currentBackground =1; 



//Add Audio to game // learned in Class //Lexture three: Loading sound in a game time 1:12:17 - 1:17:35

   InitAudioDevice();

   Sound sound = LoadSound ("SoundEffects/ballsoundmp3"); 

   Sound winner = LoadSound ("SoundEffects/crowd .mp3 ");


//Lecture two: Drawing objects onto screen (in my objects it was ball and retangles) time 1:04:16 - 1:07:32

	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300;
	ball.speedY = 300;

	Paddle leftPaddle;
	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 500;

	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 500;

	const char* winnerText = nullptr;
   

	while (!WindowShouldClose())

// adding or if statements to use for change our backgrounds every 10 seconds 
//Lexture three: Using if statements/ true and fale time 2:30-3:42 / time 35:41 - 39:32

       if (frameCount % backgroundChangeTime == 0) 
       {
          currentBackground++;
          if(currentBackground >3) currentBackground =1; 


       }
// DRAW BACKGROUNDS
//Lexture three: Using if statements/ true and fale time 2:30-3:42 / time 35:41 - 39:32

       if(currentBackground == 1)
       DrawTexture(background1,0,0, WHITE); 
      
       else if(currentBackground ==2)

       DrawTexture (background2,0,0, WHITE);

       else if (currentBackground == 3)
       DrawTexture (background3, 0,0,  WHITE);

       frameCount++;


//Lecture two: How speed function works time 40:38-55:03
//online tutorial  (https://youtu.be/LvpS3ILwQNA?si=hLRwl5bQKn3iCEGo) / time 29;16
	{
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY*= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}
//Lecture two: How speed function works time 40:38-55:03
// Lexture three: if statements/else statement time 35:41- 39:32
//Lexture three: Game Loop time imput statement/ keydown (using keys for different functions) time 40:20 -52:01

		if (IsKeyDown(KEY_A))
		{
			leftPaddle.y -= leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_X))
		{
			leftPaddle.y += leftPaddle.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_P))
		{
			rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_M))
		{
			rightPaddle.y += rightPaddle.speed * GetFrameTime();
    
		}

//Advanced Features: speed boost) Lecture two: How speed function works time 40:38-55:03
//tutorial (https://youtu.be/LGqsnM_WEK4?si=4JCWUoT1eMIQlpbQ) time 56;12 - 1:03:01
//Lexture three :Using Vector2 time 14:46- 19:18 

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect()))
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
			}
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
			}
		}
// adding font to the game, if ball goes off screen on left or right th below message will shwo up 
//Lexture three: Loading different fonts time 53:44- 1:06:34
		if (ball.x < 0)
		{
			winnerText = "COME ON,YOU CAN DO IT";
		}
		if (ball.x > GetScreenWidth())
		{
			winnerText = " TRY AGAIN!";

    
		}

    //resets the game 
    //Lexture three: Using if statements/ true and fale time 2:30-3:42 / time 35:41 - 39:32
		if (winnerText && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 400;
			ball.speedY = 400;
			winnerText = nullptr;
		}
		


		BeginDrawing();
			ClearBackground(WHITE);

			ball.Draw();
			leftPaddle.Draw();
			rightPaddle.Draw();

			if (winnerText)
			{
				int textWidth = MeasureText(winnerText, 60);
				DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, PINK);
			}

			
		EndDrawing();
    //Lecture 1: Set up and screen height and width, time 22:32 - 37:38

		//De-Initialization  
    //  unload background texture 
     
     UnloadTexture(background1);
     UnloadTexture(background2);
     UnloadTexture(background3);


// unloadsound

      UnloadSound(sound);
      UnloadSound(winner);

    CloseAudioDevice ();
  CloseWindow();
	}

	return 0;
}


