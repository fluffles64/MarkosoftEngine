#include <SDL.h>
#include <SDL_thread.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <SDL_ttf.h>
#include <cmath>
#include "InputManager.h"
#include "GraphicManager.h"
#include "Texture.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "PhysicsManager.h"

// Scene textures
Texture sandTexture;
Texture waterTexture;
Texture textTexture;
Texture gTimeTextTexture;
Texture typeTexture;
Texture woodTexture;
Texture lavaTexture;
Texture smokeTexture;
Texture frameTexture;

int counter = 0;
int mouseX = 0;
int mouseY = 0;
int xArr = 0;
int yArr = 0;
int myX = 0;
int myY = 0;
int brushSize = 16;
int buttonSize = 16;
int margin = 16;
std::string selected = "../../media/sand.png";
std::string selectedText = "Sand";
bool leftMIsDown = false;
bool started = false;
bool isSelecting = false;

int main(int argc, char* args[])
{
	InputManager::CreateSingleton();
	GraphicManager::CreateSingleton();
	ObjectManager::CreateSingleton();
	PhysicsManager::CreateSingleton();
	TimeManager::CreateSingleton();
	PhysicsManager::GetInstance().InitializeMatrix();

	// Start up SDL and create window
	if (!GraphicManager::GetInstance().init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		GraphicManager::GetInstance().gSandTexture = &sandTexture;
		GraphicManager::GetInstance().gWaterTexture = &waterTexture;
		GraphicManager::GetInstance().gTypeTexture = &typeTexture;
		GraphicManager::GetInstance().gTextTexture = &textTexture;
		GraphicManager::GetInstance().gWoodTexture = &woodTexture;
		GraphicManager::GetInstance().gLavaTexture = &lavaTexture;
		GraphicManager::GetInstance().gSmokeTexture = &smokeTexture;
		GraphicManager::GetInstance().gFrameTexture = &frameTexture;

		// Load media
		if (!GraphicManager::GetInstance().loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			// Main loop flag
			bool quit = false;

			// Event handler
			SDL_Event e;

			// Set text color as black
			SDL_Color textColor = { 255, 255, 255, 255 };
			SDL_Color textColor2 = { 192, 172, 116, 255 };

			// In memory text stream
			std::stringstream timeText;
			std::stringstream typeText;

			// Start counting frames per second
			int countedFrames = 0;

			TimeManager::GetInstance().start();

			// While application is running
			while (!quit)
			{
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					// User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					if (e.type == SDL_MOUSEWHEEL)
					{
						if (e.wheel.y > 0) //  Scroll up
						{
							if (brushSize <= 4)
								brushSize *= 4;
						}
						else if (e.wheel.y < 0) //  Scroll down
						{
							if (brushSize >= 4)
								brushSize /= 4;
						}
					}
					else if (e.type == SDL_MOUSEBUTTONDOWN)
					{

						if (e.button.button == SDL_BUTTON_LEFT)
						{
							leftMIsDown = true;
						}
					}
					else if (e.type == SDL_MOUSEBUTTONUP)
					{
						if (e.button.button == SDL_BUTTON_LEFT)
						{
							leftMIsDown = false;
						}
					}
				}

				if (leftMIsDown)
				{
					mouseX = PhysicsManager::GetInstance().RoundUp(e.button.x, 4);
					mouseY = PhysicsManager::GetInstance().RoundUp(e.button.y, 4);

					if (mouseX == 0)
					{
						xArr = 0;
					}
					else if (mouseY == 0)
					{
						yArr = 0;
					}
					else
					{
						xArr = mouseX / 4;
						yArr = mouseY / 4;
					}

					if (mouseX >= GraphicManager::GetInstance().SCREEN_WIDTH - 48 && mouseX <= GraphicManager::GetInstance().SCREEN_WIDTH - 16 && mouseY <= 48 && mouseY >= 16)
					{
						selected = "../../media/sand.png";
						selectedText = "Sand";
						textColor2 = { 192, 172, 116, 255 };
						isSelecting = true;
					}
					if (mouseX >= GraphicManager::GetInstance().SCREEN_WIDTH - 48 && mouseX <= GraphicManager::GetInstance().SCREEN_WIDTH - 16 && mouseY <= 96 && mouseY >= 64)
					{
						selected = "../../media/water.png";
						selectedText = "Water";
						textColor2 = { 48, 116, 180, 255 };
						isSelecting = true;
					}
					if (mouseX >= GraphicManager::GetInstance().SCREEN_WIDTH - 48 && mouseX <= GraphicManager::GetInstance().SCREEN_WIDTH - 16 && mouseY <= 144 && mouseY >= 112)
					{
						selected = "../../media/wood.png";
						selectedText = "Wood";
						textColor2 = { 112,68,36, 255 };
						isSelecting = true;
					}
					if (mouseX >= GraphicManager::GetInstance().SCREEN_WIDTH - 48 && mouseX <= GraphicManager::GetInstance().SCREEN_WIDTH - 16 && mouseY <= 192 && mouseY >= 160)
					{
						selected = "../../media/lava.png";
						selectedText = "Lava";
						textColor2 = { 200,44,44, 255 };
						isSelecting = true;
					}
					if (mouseX >= GraphicManager::GetInstance().SCREEN_WIDTH - 48 && mouseX <= GraphicManager::GetInstance().SCREEN_WIDTH - 16 && mouseY <= 240 && mouseY >= 208)
					{
						selected = "../../media/smoke.png";
						selectedText = "Smoke";
						textColor2 = { 136,132,132, 255 };
						isSelecting = true;
					}

					if (PhysicsManager::GetInstance().mat[xArr][yArr] == 0 && (mouseX >= 0 && mouseX < 1920 && mouseY >= 0 && mouseY < 1080) && !isSelecting)
					{
						started = true;
						PhysicsManager::GetInstance().SpawnParticles(selected, mouseX, mouseY, brushSize);
						counter += brushSize;
					}
					isSelecting = false;
				}

				// Calculate and correct fps
				float avgFPS = countedFrames / (TimeManager::GetInstance().getTicks() / 1000.f);
				if (avgFPS > 2000000)
				{
					avgFPS = 0;
				}

				// Set text to be rendered
				timeText.str("");
				timeText << "FPS: " << avgFPS;
				typeText.str("");
				typeText << " " << selectedText;

				// Render text
				if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
				{
					printf("Unable to render FPS texture!\n");
				}
				if (!typeTexture.loadFromRenderedText(typeText.str().c_str(), textColor2))
				{
					printf("Unable to render type texture!\n");
				}

				// Clear screen
				SDL_SetRenderDrawColor(GraphicManager::GetInstance().getGRenderer(), 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderClear(GraphicManager::GetInstance().getGRenderer());

				// Draw UI
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						sandTexture.render(GraphicManager::GetInstance().SCREEN_WIDTH - 48 + (4 * j), 16 + (4 * i));
						waterTexture.render(GraphicManager::GetInstance().SCREEN_WIDTH - 48 + (4 * j), 64 + (4 * i));
						woodTexture.render(GraphicManager::GetInstance().SCREEN_WIDTH - 48 + (4 * j), 112 + (4 * i));
						lavaTexture.render(GraphicManager::GetInstance().SCREEN_WIDTH - 48 + (4 * j), 160 + (4 * i));
						smokeTexture.render(GraphicManager::GetInstance().SCREEN_WIDTH - 48 + (4 * j), 208 + (4 * i));
					}
				}

				if(selectedText == "Sand")
					frameTexture.render(GraphicManager::GetInstance().SCREEN_WIDTH - 49, 15.5);
				if (selectedText == "Water")
					frameTexture.render(GraphicManager::GetInstance().SCREEN_WIDTH - 49, 63.5);
				if (selectedText == "Wood")
					frameTexture.render(GraphicManager::GetInstance().SCREEN_WIDTH - 49, 111.5);
				if (selectedText == "Lava")
					frameTexture.render(GraphicManager::GetInstance().SCREEN_WIDTH - 49, 159.5);
				if (selectedText == "Smoke")
					frameTexture.render(GraphicManager::GetInstance().SCREEN_WIDTH - 49, 207.5);

				textTexture.render(16, 16);
				gTimeTextTexture.render(16, 16);
				typeTexture.render(GraphicManager::GetInstance().SCREEN_WIDTH / 2 - 100, 16);
				GraphicManager::GetInstance().gSmokeTexture->setAlpha(50);

				//Render objects
				if (started) {
					for (int i = 0; i < counter; i++) {
						if (ObjectManager::GetInstance().objects[i]->isRenderable)
							ObjectManager::GetInstance().objects[i]->render();
					}
				}

				// Update screen
				SDL_RenderPresent(GraphicManager::GetInstance().getGRenderer());
				++countedFrames;
			}
		}

		// Free resources and close SDL
		GraphicManager::GetInstance().close();
		return 0;
	}
}