#include "bullet.h"
#include <math.h>

void bullet::draw()
{

	if (enabled)
	{
		DrawCircle(pos.x, pos.y, radius, BLACK);
	}


}

void bullet::update(float deltatime, Vector2 player, Vector2 target)
{
	Vector2 delta = { target.x - player.x,target.y - player.y };
	
	float mag = sqrt(delta.x*delta.x + delta.y * delta.y);
	delta.x /= mag;
	delta.y /= mag;

	pos.x += speed * delta.x* GetFrameTime();
	pos.y += speed * delta.y* GetFrameTime();

}
