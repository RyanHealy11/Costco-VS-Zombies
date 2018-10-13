#include "zombie.h"
#include"raylib.h"
void Zombies::draw()
{
	if (enabled) 
	{
		if (fast)
		{
			DrawCircle(pos.x, pos.y, radius, { 0, 0, 255, 255 });
		}
		else if (fat)
		{
			DrawCircle(pos.x, pos.y, radius, { 0, 255, 255, 255 });
		}
		else
		{
			DrawCircle(pos.x, pos.y, radius, DARKGREEN);
		}
	}
}
void Zombies::update(float deltatime, float targetX, float targetY)
{
	if (pos.x >= 200)
	{
		pos.x -= speed * deltatime;
	}
	else 
	{
		if (targetY < pos.y)
		{
			pos.y -= speed * deltatime;
		}
		if (targetY > pos.y )
		{
			pos.y += speed * deltatime;
		}
		if (targetX < pos.x)
		{
			pos.x -= speed * deltatime;
		}
		if (targetX > pos.x)
		{
			pos.x += speed * deltatime;
		}
	}
}