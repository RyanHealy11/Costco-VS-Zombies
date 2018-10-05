#pragma once

#include"raylib.h"




class ball
{
public:
	//position
	Vector2 pos;
	//size
	float radius;

	//movement
	
	// speed
	float speed;


	void update(float deltatime);
	void draw();
};