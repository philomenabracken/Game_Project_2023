#include "raylib.h"

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
    // Determin the Game Window Width and Height. Lecture one. 
    const int screenWidth = 800;
    const int screenHeight = 450;
    const int fps= 60;
	const int backgroundChangeTime = 10* fps;

    // Initialize the Window
    InitWindow(screenWidth, screenHeight, "Paddle Crash ");

    //adding texture for the background/ cartoon effect /class lexcture/ lecture three adding textures. 

   Texture2D background1 = LoadTexture ("Assets_Resources/level one.png");

   Texture2D background2 = LoadTexture ("Assets_Resources/level two.png");

   Texture2D background3 = LoadTexture ("Assets_Resources/ level three.png");

    // Setting the Frames Per Second / lecture one 
    SetTargetFPS(60);



   // adding in frame count for background that will be displayed and number of frames that have passed for game backgrounds 
   int frameCount = 0;
   int currentBackground =1; 



//Add Audio to game // learned in Class //Lexture three: Loading sound in a game time 1:12:17 - 1:17:35

   InitAudioDevice();

   Sound sound = LoadSound ("SoundEffects/ballsoundmp3"); 

   Sound winner = LoadSound ("SoundEffects/crowd .mp3 ");

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

// adding or if statements to use for change our backgrouns every 10 seconds 

       if (frameCount % backgroundChangeTime == 0) 
       {
          currentBackground++;
          if(currentBackground >3) currentBackground =1; 


       }
// DRAW BACKGROUNDs 

       if(currentBackground == 1)
       DrawTexture(background1,0,0, WHITE); 
      
       else if(currentBackground ==2)

       DrawTexture (background2,0,0, WHITE);

       else if (currentBackground == 3)
       DrawTexture (background3, 0,0,  WHITE);

       frameCount++;



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

		if (ball.x < 0)
		{
			winnerText = "COME ON,YOU CAN DO IT";
		}
		if (ball.x > GetScreenWidth())
		{
			winnerText = " TRY AGAIN!";
		}
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


