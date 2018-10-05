

#include "raylib.h"
#include <string>
#include "player.h"
#include "zombie.h"
#include "bullet.h"
#include <ctime>
#include <iostream>
#include<fstream>
#include <sstream> 

void Restart();
int getleader(int list[]);
int setleader(int list[]);

int main()
{
	srand(time(NULL));
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;
	int score = 0;
	bool death = false;
	int zombs = 1;
	bool leaderopen = false;
	InitWindow(screenWidth, screenHeight, "zombie defense");

	SetTargetFPS(60);
	
	bullet bull;
	bull.radius = 5.0f;
	bull.speed = 1000.0f;
	bull.value = 10;
	bull.enabled = false;

	ball player;
	player.pos = { 100, 100 };
	player.radius =  10.0f ;
	player.speed = 400.0f;

	pickup zomb;
	zomb.pos.x = 750;
	zomb.pos.y = rand() % 450;
	zomb.radius = 10.0f;            
	zomb.speed = 100.0f;
	zomb.value = 50;
	zomb.enabled = true;

	pickup zombies[100];

	for (int i = 0; i < 100; ++i) 
	{
		zombies[i].pos.x = 850;
		zombies[i].pos.y = rand() % 450;
		zombies[i].radius = 10.0f;
		zombies[i].speed = 30.0f;
		zombies[i].value = 50;
		zombies[i].enabled = true;
	}
	int LeaderBoard[11];

	for (int i = 0; i < 10; ++i)
	{
		LeaderBoard[i] = 0;
	}
	//--------------------------------------------------------------------------------------

	float duration = 0;
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		
		// Update
		//----------------------------------------------------------------------------------
		player.update(GetFrameTime());
		
		if (duration > 100)	
		{
			for (int i = 0; i < 100; ++i)
			{
				zombies[i].update(GetFrameTime(), player.pos.x, player.pos.y);

			}
		}
		else if (duration < 100)
		{
			for (int i = 0; i < duration; ++i)
			{
				zombies[i].update(GetFrameTime(), player.pos.x, player.pos.y);

			}
		}
		
		if (bull.enabled)
		{
			bull.update(GetFrameTime());
		}
		
		for (int i = 0; i < 100; ++i) 
		{
			if (bull.enabled) 
			{
				if (CheckCollisionCircles(bull.pos, bull.radius, zombies[i].pos, zombies[i].radius))
				{
					zombies[i].pos.x = 850;
					zombies[i].pos.y = rand() % 450;
					bull.enabled = false;
					++score;

				}
			}
		}

		for (int i = 0; i < 100; ++i)
		{
			if (CheckCollisionCircles(player.pos, player.radius, zombies[i].pos, zombies[i].radius))
			{
				death = true;
			}
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		
			BeginDrawing();
			ClearBackground(RAYWHITE);
			if (!death)
			{
				duration += GetFrameTime();
				if (IsKeyDown(KEY_SPACE))
				{
					if (!bull.enabled) {
						bull.pos.x = player.pos.x;
						bull.pos.y = player.pos.y;
						bull.enabled = true;
					}
				}
				
				DrawRectangle(0, 0, 216, 450, GRAY);
				DrawRectangle(216, 0, 584, 450, GREEN);
		
				DrawText("C", 90, 90, 40, RED);
				DrawText("O", 90, 130, 40, RED);
				DrawText("S", 90, 170, 40, RED);
				DrawText("T", 90, 210, 40, RED);
				DrawText("C", 90, 250, 40, RED);
				DrawText("O", 90, 290, 40, RED);
				if (bull.enabled)
				{
					bull.draw();
					if (bull.pos.x >= 800) 
					{
						bull.enabled = false;
					}
				}


				for (int i = 0; i < 100; ++i)
				{
					zombies[i].draw();
				}
				
				player.draw();
				DrawText("Score", 3, 0, 20, LIGHTGRAY);
				DrawText(std::to_string(score).c_str(), 70, 0, 20, LIGHTGRAY);

				if (player.pos.x <= 0) { player.pos.x = 0; }
				if (player.pos.x >= 200) { player.pos.x = 200; }
				if (player.pos.y <= 0) { player.pos.y = 0; }
				if (player.pos.y >= 450) { player.pos.y = 450; }
				
				DrawText("Time", 330, 0, 20, LIGHTGRAY);
				DrawText(std::to_string(duration).c_str(), 380, 0, 20, LIGHTGRAY);
			}
			if (death)
			{
				
				DrawText(("Congrats You Killed " +  (std::to_string(score)) + " Zombies!").c_str(), 190, 90, 20, RED);
				int finish = duration;
				DrawText(("And survived " + (std::to_string(finish)) + " seconds!").c_str(), 190, 110, 20, RED);
				DrawText("Would you like to restart? y/n", 190, 130, 20, RED);
				for (int i = 0; i < 10; ++i)
				{
					std::string temp = std::to_string(i + 1);
					DrawText ((temp + ": " + std::to_string(LeaderBoard[i])).c_str(), 190, (150 + (i * 20)), 20, RED);
				}
				
				if (leaderopen ==false) 
				{
					getleader(LeaderBoard);
					LeaderBoard[10] = score;
					setleader(LeaderBoard);
					leaderopen = true;
				}

				if (IsKeyDown(KEY_Y)) 
				{
					CloseWindow();
					Restart();
				}
				if (IsKeyDown(KEY_N))
				{
					return 0;
				}

			}	

			EndDrawing();
		
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}


int getleader(int list[])
{
	std::fstream file;
	file.open( "LeaderBoard.bin", std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "error opening file" << std::endl;
		return 0;
	}
	for (int i = 0; i < 10; ++i) 
	{
		std::string buffer;
		std::getline(file, buffer);
		
		std::stringstream geek(buffer);
		
		geek >> list[i];
		
	}

	file.flush();
	file.close();
	return 0;
}

int setleader(int list[]) 
{
	std::fstream file;
	file.open("LeaderBoard.bin", std::ios::out | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "error opening file" << std::endl;
		return 0;
	}
	int correct = 0;
	do
	{
		int temp;
		correct = 0;
		for (int i = 0; i < 10; ++i)
		{
			if (list[i] < list[i + 1])
			{
				temp = list[i + 1];
				list[i + 1] = list[i];
				list[i] = temp;

			}
			else if (list[i] >= list[i + 1])
			{
				++correct;
			}
		}
	} while (correct != 10);

	for (int i = 0; i < 10; ++i)
	{
		file << list[i] << std::endl;

	}
	file.flush();
	file.close();
	return 0;


}
void Restart() 
{
	main();
}


