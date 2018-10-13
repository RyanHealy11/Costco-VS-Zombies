#pragma once
#include"raylib.h"


class Zombies
{
public:
	Vector2 pos;

	float radius;
	float speed;
	int value;
	int health;
	bool enabled;
	bool fast = false;
	bool fat = false;

	void draw();
	void update(float deltatime, float targetX, float targetY);
};