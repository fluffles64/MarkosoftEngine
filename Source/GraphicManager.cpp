#include "GraphicManager.h"
#include <vector>

void GraphicManager::Draw(SDL_Texture* mySprite, float x, float y, float rot, float scale) {}

void GraphicManager::DrawText(string text) {}

void GraphicManager::CleanScreen() {}

void GraphicManager::Update(void) {}

void GraphicManager::setGRenderer(SDL_Renderer* myRenderer)
{
	this->gRenderer = myRenderer;
}

bool GraphicManager::init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("Pixel Simulation Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				// Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool GraphicManager::loadMedia()
{
	// Loading success flag
	bool success = true;

	// Open the font
	gFont = TTF_OpenFont("../../media/pixelmix.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		// Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (!gTextTexture->loadFromRenderedText("FPS: ", textColor))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	// Load textures with standard alpha blending
	const std::vector<std::pair<Texture*, const char*>> textures = {
		{ gSandTexture, "../../media/sand.png" },
		{ gWaterTexture, "../../media/water.png" },
		{ gWoodTexture, "../../media/wood.png" },
		{ gLavaTexture, "../../media/lava.png" },
		{ gSmokeTexture, "../../media/smoke.png" },
		{ gFrameTexture, "../../media/frame.png" }
	};

	for (auto& texturePair : textures)
	{
		if (!texturePair.first->loadFromFile(texturePair.second))
		{
			printf("Failed to load %s texture!\n", texturePair.second);
			success = false;
		}
		else
		{
			// Set standard alpha blending
			texturePair.first->setBlendMode(SDL_BLENDMODE_BLEND);
		}
	}

	return success;
}

void GraphicManager::close()
{
	// Free loaded images
	gSandTexture->free();
	gWaterTexture->free();
	gWoodTexture->free();
	gLavaTexture->free();
	gTextTexture->free();
	gSmokeTexture->free();
	gFrameTexture->free();

	// Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	// Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void GraphicManager::setWindowAndRenderer()
{
	gSandTexture->setWindowAndRenderer(gWindow, gRenderer);
	gWaterTexture->setWindowAndRenderer(gWindow, gRenderer);
	gWoodTexture->setWindowAndRenderer(gWindow, gRenderer);
	gLavaTexture->setWindowAndRenderer(gWindow, gRenderer);
	gSmokeTexture->setWindowAndRenderer(gWindow, gRenderer);
}