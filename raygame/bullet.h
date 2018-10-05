#pragma once
#include"raylib.h"
class bullet
{
public:
	Vector2 pos;

	float radius;
	float speed;
	int value;

	bool enabled;

	void draw();
	void update(float deltatime);
};
