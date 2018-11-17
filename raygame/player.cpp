#include "player.h"
#include"raylib.h"
void ball::update(float deltatime)
{

	if (IsKeyDown(KEY_W) or IsKeyDown(KEY_UP))
	{
		pos.y -= speed * deltatime;
	}
	if (IsKeyDown(KEY_S) or IsKeyDown(KEY_DOWN))
	{
		pos.y += speed * deltatime;
	}
	if (IsKeyDown(KEY_A) or IsKeyDown(KEY_LEFT))
	{
		pos.x -= speed * deltatime;
	}
	if (IsKeyDown(KEY_D) or IsKeyDown(KEY_RIGHT))
	{
		pos.x += speed * deltatime;
	}

}

void ball::draw()
{

	DrawCircle(pos.x, pos.y, radius, SKYBLUE);

}
