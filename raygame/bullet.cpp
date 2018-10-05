#include "bullet.h"

void bullet::draw()
{

	if (enabled)
	{
		DrawCircle(pos.x, pos.y, radius, BLACK);
	}


}

void bullet::update(float deltatime)
{

	if (enabled)
	{
		pos.x += speed * deltatime;
	}
}
