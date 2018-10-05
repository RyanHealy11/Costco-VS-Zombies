#pragma once
#include"raylib.h"


class pickup
{
public:
	Vector2 pos;

	float radius;
	float speed;
	int value;

	bool enabled;

	void draw();
	void update(float deltatime, float targetX, float targetY);
};