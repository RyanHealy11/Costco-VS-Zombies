

#include "raylib.h"
#include <string>
#include "player.h"
#include "zombie.h"
#include "bullet.h"
#include <ctime>
#include <iostream>
#include<fstream>
#include <sstream> 
#include "Leaderboard.h"

void Restart();
int getleader(Leaderstuff list[]);
int setleader(Leaderstuff list[]);

int main()
{
	srand(time(NULL));
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 900;
	int screenHeight = 450;
	int score = 0;
	bool death = false;
	int zombs = 1;
	bool leaderopen = false;
	int bullshitluck = 0;
	int multi = 1;
	std::string buffer;
	int namelimit = 0;
	bool nameentered = false;
	int fastspawn = 0;
	int fatspawn = 0;

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

	Zombies zomb;
	zomb.pos.x = 750;
	zomb.pos.y = rand() % 450;
	zomb.radius = 10.0f;            
	zomb.speed = 30.0f;
	zomb.value = 50;
	zomb.enabled = true;

	Zombies fastZombies[10];
	Zombies fatZombies[10];
	Zombies zombies[100];


	for (int i = 0; i < 10; ++i)
	{
		fatZombies[i].pos.x = 850;
		fatZombies[i].pos.y = rand() % 450;
		fatZombies[i].radius = 20.0f;
		fatZombies[i].speed = 10.0f;
		fatZombies[i].value = 50;
		fatZombies[i].enabled = true;
		fatZombies[i].fat = true;
		fatZombies[i].health = 10;
	}

	for (int i = 0; i < 10; ++i)
	{
		fastZombies[i].pos.x = 850;
		fastZombies[i].pos.y = rand() % 450;
		fastZombies[i].radius = 10.0f;
		fastZombies[i].speed = 90.0f;
		fastZombies[i].value = 50;
		fastZombies[i].enabled = true;
		fastZombies[i].fast = true;
	}

	for (int i = 0; i < 100; ++i) 
	{
		zombies[i].pos.x = 850;
		zombies[i].pos.y = rand() % 450;
		zombies[i].radius = 10.0f;
		zombies[i].speed = 30.0f;
		zombies[i].value = 50;
		zombies[i].enabled = true;
	}
	Leaderstuff LeaderBoard[11];

	for (int i = 0; i < 10; ++i)
	{
		LeaderBoard[i].score = 0;
	}
	//--------------------------------------------------------------------------------------
	/*score = 10000;*/
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
		
		if (fastspawn <= 10) 
		{
			for (int i = 0; i < fastspawn; i++)
			{
				fastZombies[i].update(GetFrameTime(), player.pos.x, player.pos.y);
			}
		}
		else 
		{
			for (int i = 0; i < 10; i++)
			{
				fastZombies[i].update(GetFrameTime(), player.pos.x, player.pos.y);
			}
		}
		fastspawn = (score / 5000);

		if (fatspawn <= 10)
		{
			for (int i = 0; i < fatspawn; i++)
			{
				fatZombies[i].update(GetFrameTime(), player.pos.x, player.pos.y);
			}
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				fatZombies[i].update(GetFrameTime(), player.pos.x, player.pos.y);
			}
		}
		fatspawn = (score / 10000);
		
		if (bull.enabled)
		{
			bull.update(GetFrameTime());
		}
		
		
		
		for (int i = 0; i < 10; i++)
		{
			if (CheckCollisionCircles(player.pos, player.radius, fastZombies[i].pos, fastZombies[i].radius))
			{
				death = true;
			}
			if (CheckCollisionCircles(player.pos, player.radius, fatZombies[i].pos, fatZombies[i].radius))
			{
				death = true;
			}
			if (bull.enabled)
			{
				if (CheckCollisionCircles(bull.pos, bull.radius, fastZombies[i].pos, fastZombies[i].radius))
				{
					bullshitluck = rand() % 1000;

					if (bullshitluck == 666)
					{
						fastZombies[i].pos.x = 1;
						fastZombies[i].pos.y = rand() % 450;
						bull.enabled = false;
						score += (multi * 2);
						++multi;
					}
					else
					{
						fastZombies[i].pos.x = 850;
						fastZombies[i].pos.y = rand() % 450;
						bull.enabled = false;
						score += (multi * 2);
						++multi;
					}
				}
				if (CheckCollisionCircles(bull.pos, bull.radius, fatZombies[i].pos, fatZombies[i].radius))
				{
					bullshitluck = rand() % 1000;
					--fatZombies[i].health;


					if (fatZombies[i].health <= 0) 
					{
						if (bullshitluck == 666)
						{
							fatZombies[i].pos.x = 1;
							fatZombies[i].pos.y = rand() % 450;
							bull.enabled = false;
							score += (multi * 5);
							++multi;
							fatZombies[i].health = 10;
						}
						else
						{
							fatZombies[i].pos.x = 850;
							fatZombies[i].pos.y = rand() % 450;
							bull.enabled = false;
							score += (multi * 5);
							++multi;
							fatZombies[i].health = 10;
						}
					}
					bull.enabled = false;
				}
			}
		}
		for (int i = 0; i < 100; ++i) 
		{
			if (CheckCollisionCircles(player.pos, player.radius, zombies[i].pos, zombies[i].radius))
			{
				death = true;
			}
			if (bull.enabled) 
			{
				if (CheckCollisionCircles(bull.pos, bull.radius, zombies[i].pos, zombies[i].radius))
				{
					bullshitluck = rand() % 1000;
					
					if (bullshitluck == 666) 
					{
						zombies[i].pos.x = 1;
						zombies[i].pos.y = rand() % 450;
						bull.enabled = false;
						score += multi;
						++multi;
					}
					else 
					{
						zombies[i].pos.x = 850;
						zombies[i].pos.y = rand() % 450;
						bull.enabled = false;
						score += multi;
						++multi;
					}					
				}
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
				if (IsKeyDown(KEY_SPACE) or IsMouseButtonDown(MOUSE_LEFT_BUTTON))
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
						multi = 1;
						bull.enabled = false;
					}
				}


				for (int i = 0; i < 100; ++i)
				{
					zombies[i].draw();
				}
				for (int i = 0; i < 10; i++)
				{
					fastZombies[i].draw();
					fatZombies[i].draw();
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
			if ((death) and (!nameentered))
			{
				
				DrawText(("Congrats You Killed " +  (std::to_string(score)) + " Zombies!").c_str(), 190, 90, 20, BLACK);
				int finish = duration;
				DrawText(("And survived " + (std::to_string(finish)) + " seconds!").c_str(), 190, 110, 20, BLACK);
				DrawText("What would you like to be know by", 190, 130, 20, BLACK);
				

				if (IsKeyPressed(KEY_ENTER) and namelimit == 3) 
				{
					nameentered = true;
				}
				else if (IsKeyPressed(KEY_BACKSPACE) and (namelimit != 0))
				{
					buffer.erase(buffer.begin() + (namelimit - 1));
					--namelimit;
				}
				else if ((GetKeyPressed() != -1) and (namelimit <= 2))
				{
					buffer += GetKeyPressed();
					++namelimit;
				}

				DrawText((buffer).c_str(), 290, 230, 20, BLACK);

			}	
			else if ((death) and (nameentered)) 
			{
			
				if (leaderopen == false) 
				{
					getleader(LeaderBoard);
					LeaderBoard[10].score = score;
					LeaderBoard[10].name = buffer;
					setleader(LeaderBoard);
					leaderopen = true;
				}

				for (int i = 0; i < 10; ++i)
				{
					std::string temp = std::to_string(i + 1);
					DrawText ((temp + ": " + LeaderBoard[i].name + "   " + std::to_string(LeaderBoard[i].score)).c_str(), 190, (150 + (i * 20)), 20, BLACK);
				}

				DrawText("Would you like to restart? y/n", 190, 130, 20, BLACK);
				
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


int getleader(Leaderstuff list[])
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
		geek >> list[i].score;
		
		std::getline(file, buffer);
		list[i].name = buffer;
		
	}

	file.flush();
	file.close();
	return 0;
}

int setleader(Leaderstuff list[])
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
		std::string temp2;
		correct = 0;
		for (int i = 0; i < 10; ++i)
		{
			if (list[i].score < list[i + 1].score)
			{
				temp = list[i + 1].score;
				list[i + 1].score = list[i].score;
				list[i].score = temp;

				temp2 = list[i + 1].name;
				list[i + 1].name = list[i].name;
				list[i].name = temp2;
			}
			else if (list[i].score >= list[i + 1].score)
			{
				++correct;
			}
		}
	} while (correct != 10);

	for (int i = 0; i < 10; ++i)
	{
		file << list[i].score << std::endl;
		file << list[i].name << std::endl;
	}
	file.flush();
	file.close();
	return 0;


}
void Restart() 
{
	main();
}


