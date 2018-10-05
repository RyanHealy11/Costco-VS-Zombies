#include "zombie.h"
#include"raylib.h"
void pickup::draw()
{
	if (enabled) 
	{
		DrawCircle(pos.x, pos.y, radius, DARKGREEN);
	}
}
void pickup::update(float deltatime, float targetX, float targetY)
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