#pragma once
#include "Singleton.h"
#include "SDL.h"
#include <SDL.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <Texture.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;

class GraphicManager : public Singleton<GraphicManager>
{
	friend class Singleton<GraphicManager>;

private:
	SDL_Texture* sprite;
	string text;
	float xPos;
	float yPos;
	float rotation;
	float scale;
	float screenPos;
	float screenSize;
	int mWidth;
	int mHeight;

	// Private constructor to avoid more than one instance
	GraphicManager() {};

public:
	// Screen dimension constants
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	// Globally used font
	TTF_Font* gFont = NULL;

	// Font texture
	Texture* gTextTexture;
	Texture* gTypeTexture;

	// Scene textures
	Texture* gSandTexture;
	Texture* gWaterTexture;
	Texture* gWoodTexture;
	Texture* gLavaTexture;
	Texture* gSmokeTexture;
	Texture* gFrameTexture;

	Texture* mTexture;

	// The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	// The window renderer
	SDL_Renderer* gRenderer = NULL;

	// Creates image from font string
	SDL_Renderer* getGRenderer() { return this->gRenderer; };
	void setGRenderer(SDL_Renderer* myRenderer);
	void Draw(SDL_Texture* mySprite, float x, float y, float rot, float scale);
	void DrawText(string text);
	void CleanScreen();
	void Update(void);

	// Starts up SDL and creates window
	bool init();

	// Loads media
	bool loadMedia();

	// Frees media and shuts down SDL
	void close();
	void setWindowAndRenderer();
};