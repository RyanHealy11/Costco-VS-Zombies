

#include "raylib.h"
#include <string>
#include "player.h"
#include "zombie.h"
#include "bullet.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream> 
#include "Leaderboard.h"

void Restart();
int getleader(Leaderstuff list[]);
int setleader(Leaderstuff list[]);
void collisioncheck(Zombies zlist[], bullet& bull, ball player, bool& death, unsigned int& score ,int& multi, int zombcount);


int main() 
{
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "zombie defense");


	Vector2 PlayBorderpos = { 300,100 };
	Vector2 LeaderBorderpos = { 300, 200};
	Vector2 ExitBorderpos = { 300, 300};
	Rectangle BorderRec = {0, 0, 150, 75};
	Rectangle PlayButton = { 300,100,150,75, };
	Rectangle LeaderButton = { 300, 200, 150, 75 };
	Rectangle ExitButton = { 300, 300, 150, 75 };
	Image buttonBorder = LoadImage("textures/Border.png");
	ImageResize(&buttonBorder, BorderRec.width, BorderRec.height);
	Texture2D PlayBorder = LoadTextureFromImage(buttonBorder);
	int Game();
	int LeaderBoard(Texture2D image);

	while (!WindowShouldClose()) {
		//update start
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
		{
			Vector2 mPos = GetMousePosition();
		
			if (CheckCollisionPointRec(mPos, PlayButton)) { Game(); }
			if (CheckCollisionPointRec(mPos, LeaderButton)) { LeaderBoard(PlayBorder); }
			if (CheckCollisionPointRec(mPos, ExitButton)) { CloseWindow(); return 0; }
				
		}
		//update end


		BeginDrawing(); //drawing start
		ClearBackground(RAYWHITE);


		DrawRectangleRec(PlayButton, RED);
		DrawTextureRec(PlayBorder, BorderRec, PlayBorderpos, BLACK);
		DrawText("Play", 340, 125, 30, BLACK);

		DrawRectangleRec(LeaderButton, RED);
		DrawTextureRec(PlayBorder, BorderRec, LeaderBorderpos, BLACK);
		DrawText("Leaderboard", 310, 230, 20, BLACK);

		DrawRectangleRec(ExitButton, RED);
		DrawTextureRec(PlayBorder, BorderRec, ExitBorderpos, BLACK);
		DrawText("Exit",348, 325, 30, BLACK);

		EndDrawing(); //drawing end


	}


	CloseWindow();
}

int Game()
{
	srand(time(NULL));
	// Initialization
	//--------------------------------------------------------------------------------------
	
	unsigned int score = 0;
	bool death = false;
	
	bool leaderopen = false;
	int bullshitluck = 0;
	int multi = 1;
	std::string buffer;
	int namelimit = 0;
	bool nameentered = false;
	bool scorefinalized = false;
	int fastspawn = 0;
	int fatspawn = 0;
	int bossspawn = 0;
	unsigned int finalscore;
	bool loaded = false;
	Vector2 target;
	Vector2 players;
	Texture2D costco = LoadTexture("textures/costco.png");
	Vector2 costcopos{ 50,420 };
	

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
	Zombies bossZombies[5];
	Zombies zombies[100];

	//fat
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
		fatZombies[i].starthealth = 10;
		fatZombies[i].scoremulti = 5;
	}
	//fast
	for (int i = 0; i < 10; ++i)
	{
		fastZombies[i].pos.x = 850;
		fastZombies[i].pos.y = rand() % 450;
		fastZombies[i].radius = 10.0f;
		fastZombies[i].speed = 90.0f;
		fastZombies[i].value = 50;
		fastZombies[i].enabled = true;
		fastZombies[i].fast = true;
		fastZombies[i].health = 1;
		fastZombies[i].starthealth = 1;
		fastZombies[i].scoremulti = 2;
	}
	//boss
	for (int i = 0; i < 5; ++i) 
	{
		bossZombies[i].pos.x = 930;
		bossZombies[i].pos.y = rand() % 450;
		bossZombies[i].radius = 100.0f;
		bossZombies[i].speed = 5.0f;
		bossZombies[i].value = 50;
		bossZombies[i].enabled = true;
		bossZombies[i].boss = true;
		bossZombies[i].health = 100;
		bossZombies[i].starthealth = 100;
		bossZombies[i].scoremulti = 10;
	}
	//grunts
	for (int i = 0; i < 100; ++i) 
	{
		zombies[i].pos.x = 850;
		zombies[i].pos.y = rand() % 450;
		zombies[i].radius = 10.0f;
		zombies[i].speed = 30.0f;
		zombies[i].value = 50;
		zombies[i].enabled = true;
		zombies[i].health = 1;
		zombies[i].starthealth = 1;
		zombies[i].scoremulti = 1;
	}
	
	//seting leaderboard
	Leaderstuff LeaderBoard[11];
	for (int i = 0; i < 10; ++i)
	{
		LeaderBoard[i].score = 0;
	}
	//--------------------------------------------------------------------------------------
	/*score = 1000000;
	multi = 1;*/
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

		if (bossspawn <= 5)
		{
			for (int i = 0; i < bossspawn; i++)
			{
				bossZombies[i].update(GetFrameTime(), player.pos.x, player.pos.y);
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				bossZombies[i].update(GetFrameTime(), player.pos.x, player.pos.y);
			}
		}
		bossspawn = (score / 100000);
		
		if (bull.enabled){ bull.update(GetFrameTime(), players, target); }
		
		collisioncheck(bossZombies,bull,player,death,score,multi,5);
		collisioncheck(fastZombies, bull, player, death, score, multi, 10);
		collisioncheck(fatZombies, bull, player, death, score, multi, 10);
		collisioncheck(zombies, bull, player, death, score, multi, 100);
				
		//----------------------------------------------------------------------------------
		// Draw
		//----------------------------------------------------------------------------------
		
			BeginDrawing();
			ClearBackground(RAYWHITE);
			if (!death)
			{
				
				//timer
				duration += GetFrameTime();
				
				//spawns the bullet to the screen
				if (IsKeyDown(KEY_SPACE) or IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					if (!bull.enabled) {
						target = GetMousePosition();
						players = player.pos;
						bull.pos.x = player.pos.x;
						bull.pos.y = player.pos.y;
						bull.enabled = true;
					}
				}
				
				//draws the roof to the screen
				DrawRectangle(0, 0, 216, 450, GRAY);
				DrawRectangle(216, 0, 584, 450, GREEN);
		
				//displays the costco on the roof
				DrawTextureEx(costco, costcopos, 270, 0.75f, WHITE);
						
				//drawing the bullet to the screen
				if (bull.enabled)
				{
					bull.draw();
					if (bull.pos.x >= (GetScreenWidth() + 10) or bull.pos.x <= -10) 
					{
						--multi;
						if (multi < 0) { multi = 0; }
						bull.enabled = false;
					}
					if (bull.pos.y >= (GetScreenHeight() + 10) or bull.pos.y <= -10)
					{
						--multi;
						if (multi < 0) { multi = 0; }
						bull.enabled = false;
					}
				}

				//drawing zombs to the screen 
				for (int i = 0; i < 100; i++)
				{
					zombies[i].draw();
				}
				for (int i = 0; i < 10; i++)
				{
					fastZombies[i].draw();
					fatZombies[i].draw();
				}
				for (int i = 0; i < 5; i++)
				{
					bossZombies[i].draw();
				}
				
				//display score in top left of screen
				DrawText("Score", 3, 0, 20, LIGHTGRAY);
				DrawText(std::to_string(score).c_str(), 70, 0, 20, LIGHTGRAY);
				
				//displays the current muliplier 
				DrawText("Multiplier", 3, 20, 20, LIGHTGRAY);
				DrawText(std::to_string(multi).c_str(), 100, 20, 20, LIGHTGRAY);
				
				//draws the player to the screen
				player.draw();

				//makes sure the player stays on the roof
				if (player.pos.x <= 10) { player.pos.x = 10; }
				if (player.pos.x >= 200) { player.pos.x = 200; }
				if (player.pos.y <= 0) { player.pos.y = 0; }
				if (player.pos.y >= 450) { player.pos.y = 450; }
				
				//displays the time to the screen
				DrawText("Time", 330, 0, 20, BLACK);
				DrawText(std::to_string(duration).c_str(), 380, 0, 20, BLACK);

			}
			if ((death) and (!nameentered))
			{
				// sets final timer
				int finish = duration;
				if (!scorefinalized) 
				{
					scorefinalized = true;
					finalscore = score;
				}
				//displays score and final time as well as prompting for a name to enter
				DrawText(("Congrats Your Score was " +  (std::to_string(finalscore))).c_str(), 190, 90, 20, BLACK);
				DrawText(("And survived " + (std::to_string(finish)) + " seconds!").c_str(), 190, 110, 20, BLACK);
				DrawText("What would you like to be know by", 190, 130, 20, BLACK);
				DrawText("Press Enter when done", 190, 230, 20, BLACK);
				
				//-----------------------------------------------------------------
				// leaderboard name stuff
				//-----------------------------------------------------------------
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

				DrawText((buffer).c_str(), 290, 180, 30, BLACK);
				//-----------------------------------------------------------------
			}	
			else if ((death) and (nameentered)) 
			{
				int finish = duration;
				if (leaderopen == false) 
				{
					getleader(LeaderBoard);
					LeaderBoard[10].score = finalscore;
					LeaderBoard[10].name = buffer;
					setleader(LeaderBoard);
					leaderopen = true;
				}

				for (int i = 0; i < 10; ++i)
				{
					std::string temp = std::to_string(i + 1);
					DrawText((temp + ": ").c_str(), 300, (150 + (i * 20)), 20, BLACK);
					DrawText((LeaderBoard[i].name).c_str(), 330, (150 + (i * 20)), 20, BLACK);
					DrawText((std::to_string(LeaderBoard[i].score)).c_str(), 380, (150 + (i * 20)), 20, BLACK);
				}

				DrawText(("Congrats Your Score was " + (std::to_string(finalscore))).c_str(), 190, 90, 20, BLACK);
				DrawText(("And survived " + (std::to_string(finish)) + " seconds!").c_str(), 190, 110, 20, BLACK);

				DrawText("Would you like to restart? y/n", 230, 370, 20, BLACK);
				
				if (IsKeyDown(KEY_Y))
				{
					Game();
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
	/*CloseWindow();*/        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

int LeaderBoard(Texture2D image)
{
	Leaderstuff LeaderBoard[11];

	for (int i = 0; i < 10; ++i)
	{
		LeaderBoard[i].score = 0;
	}
	getleader(LeaderBoard);

	Vector2 BackBorderpos = { 300, 350 };
	Rectangle BorderRec = { 0, 0, 150, 75 };
	Rectangle BackButton = { 300,350,150,75, };

	while (!WindowShouldClose()) 
	{

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
		{
			Vector2 mPos = GetMousePosition();

			if (CheckCollisionPointRec(mPos, BackButton)) { return 0; }
			
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		

		DrawRectangleRec(BackButton, RED);
		DrawTextureRec(image, BorderRec, BackBorderpos, BLACK);
		DrawText("BACK", 335, 375, 30, BLACK);
		
		DrawText("Current Leaders", 270, 105 , 25, BLACK);
		for (int i = 0; i < 10; ++i)
		{
			std::string temp = std::to_string(i + 1);
			DrawText((temp + ": ").c_str() , 300, (130 + (i * 20)), 20, BLACK);
			DrawText((LeaderBoard[i].name).c_str(), 330, (130 + (i * 20)), 20, BLACK);
			DrawText((std::to_string(LeaderBoard[i].score)).c_str(), 380, (130 + (i * 20)), 20, BLACK);
		}
		EndDrawing();
	}
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

void collisioncheck(Zombies zlist[], bullet& bull, ball player, bool& death, unsigned int& score, int& multi, int zombcount)
{

	for (int i = 0; i < zombcount; i++)
	{
		if (CheckCollisionCircles(player.pos, player.radius, zlist[i].pos, zlist[i].radius))
		{
			death = true;
		}
		if (bull.enabled)
		{
			if (CheckCollisionCircles(bull.pos, bull.radius, zlist[i].pos, zlist[i].radius))
			{
				int bullshitluck = rand() % 1000;
				--zlist[i].health;
				bull.enabled = false;

				if (zlist[i].health <= 0)
				{
					if (bullshitluck == 666)
					{

						zlist[i].pos.x = 1;
						zlist[i].pos.y = rand() % 450;
						bull.enabled = false;
						score += (multi * zlist[i].scoremulti);
						++multi;
						zlist[i].health = zlist[i].starthealth;
					}
					else
					{
						zlist[i].pos.x = 850;
						zlist[i].pos.y = rand() % 450;
						bull.enabled = false;
						score += (multi * zlist[i].scoremulti);
						++multi;
						zlist[i].health = zlist[i].starthealth;
					}
				}
			}
		}
	}
}

void Restart() 
{
	main();
}


