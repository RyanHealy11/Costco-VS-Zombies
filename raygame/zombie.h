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
	int starthealth;
	bool enabled;
	int scoremulti;
	bool fast = false;
	bool fat = false;
	bool boss = false;

	void draw();
	void update(float deltatime, float targetX, float targetY);
};