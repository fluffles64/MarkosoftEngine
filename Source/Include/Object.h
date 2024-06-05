#pragma once
#include "SDL.h"
#include "GraphicManager.h"
#include <SDL.h>
#include <stdio.h>
#include <string>

enum class ObjectType {
	Sand,
	Wood,
	Water,
	Lava,
	Smoke
};

class Object
{
private:
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;
	float xPos;
	float yPos;
	Texture* texture;

public:
	static const int DOT_WIDTH = 4;
	static const int DOT_HEIGHT = 4;
	static const int DOT_VEL = 1;
	ObjectType type;
	bool settled = false;

	Object(int mX, int mY, ObjectType objectType, Texture* tex);
	~Object();

	//Takes key presses and adjusts the dot's velocity
	virtual void handleEvent(SDL_Event& e);

	//Moves the dot
	virtual void move();

	//Shows the dot on the screen
	virtual void render();
	virtual void OnCollisionEnter();
	virtual void Update(void);

	bool isRenderable = true;
	int mVelX = 0;
	int mVelY = 4;
	int mPosY = 0;
	int mPosX = 0;
};