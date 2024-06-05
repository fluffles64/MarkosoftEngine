#include "PhysicsManager.h"

int threadFunction(void* data)
{
	int index = (int)data;
	bool quit = false;

	// Cache singleton instances
	auto& physics = PhysicsManager::GetInstance();
	auto& objectManager = ObjectManager::GetInstance();

	while (!quit)
	{
		if (SDL_mutexP(physics.mut[index]) == -1)
		{
			fprintf(stderr, "Couldn't lock mutex\n");
			exit(-1);
		}

		// Iterate over the objects in the object manager
		for (Object* obj : objectManager.objects)
		{
			if (obj->settled) { continue; }

			int myX = obj->mPosX / 4;
			int myY = obj->mPosY / 4;

			if (index == 0)
			{
				// Sand simulation
				if (obj->type == ObjectType::Sand)
				{
					if (myY < physics.GRID_HEIGHT && myY >= 0 && myX < physics.GRID_WIDTH && myX >= 0)
					{
						if (physics.grid[myX][myY + 1] < 1)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosY += 4;
							physics.grid[myX][myY + 1] = 1;
						}
						else if (physics.grid[myX][myY + 1] == 2 || physics.grid[myX][myY + 1] == 3)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosY += 4;
							physics.grid[myX][myY + 1] = 1;
						}
						else if (physics.grid[myX + 1][myY + 1] < 1 && myX > 0)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosX += 4;
							obj->mPosY += 4;
							physics.grid[myX + 1][myY + 1] = 1;
						}
						else if (physics.grid[myX - 1][myY + 1] < 1 && myX > 0)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosX -= 4;
							obj->mPosY += 4;
							physics.grid[myX - 1][myY + 1] = 1;
						}
						//else
						//{
						//	// TODO: Revise the algorithm so that objects can settle without bumping into eachother prematurely
						//	obj->settled = true;
						//}
					}
				}
			}

			if (index == 1)
			{
				// Water simulation
				if (obj->type == ObjectType::Water && obj->isRenderable)
				{
					if (myY < physics.GRID_HEIGHT && myY >= 0 && myX < physics.GRID_WIDTH && myX >= 0)
					{
						// Down
						if (physics.grid[myX][myY + 1] < 1)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosY += 4;
							physics.grid[myX][myY + 1] = 2;
						}
						// Down Right
						else if (physics.grid[myX + 1][myY + 1] < 1 && myX > 0 && myX < physics.GRID_WIDTH)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosX += 4;
							obj->mPosY += 4;
							physics.grid[myX + 1][myY + 1] = 2;
						}
						// Down left
						else if (physics.grid[myX - 1][myY + 1] < 1 && myX > 0 && myX < physics.GRID_WIDTH)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosX -= 4;
							obj->mPosY += 4;
							physics.grid[myX - 1][myY + 1] = 2;
						}
						// Right
						else if (physics.grid[myX + 1][myY] < 1 && myX > 0 && myX < physics.GRID_WIDTH)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosX += 4;
							physics.grid[myX + 1][myY] = 2;
						}
						// Left
						else if (physics.grid[myX - 1][myY] < 1 && myX > 0 && myX < physics.GRID_WIDTH)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosX -= 4;
							physics.grid[myX - 1][myY] = 2;
						}
					}
				}
			}

			if (index == 2)
			{
				// Wood simulation
				if (myY < physics.GRID_HEIGHT && myY >= 0 && myX < physics.GRID_WIDTH && myX >= 0)
				{
					if (obj->type == ObjectType::Wood && obj->isRenderable)
					{
						if (myY < physics.GRID_HEIGHT && myY >= 0 && myX < physics.GRID_WIDTH && myX >= 0)
						{
							if (physics.grid[myX][myY] < 1)
							{
								physics.grid[myX][myY] = 4;
							}
							else if (physics.grid[myX][myY - 1] == 3)
							{
								physics.grid[myX][myY] = 0;
								obj->isRenderable = false;
								obj->~Object();
							}
						}
					}
					// Lava simulation
					if (obj->type == ObjectType::Lava && obj->isRenderable)
					{
						// Down
						if (physics.grid[myX][myY + 1] < 1)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosY += 4;
							physics.grid[myX][myY + 1] = 3;
						}
						// Down Right
						else if (physics.grid[myX + 1][myY + 1] < 1 && myX > 0 && myX < physics.GRID_WIDTH)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosX += 4;
							obj->mPosY += 4;
							physics.grid[myX + 1][myY + 1] = 3;
						}
						// Down left
						else if (physics.grid[myX - 1][myY + 1] < 1 && myX > 0 && myX < physics.GRID_WIDTH)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosX -= 4;
							obj->mPosY += 4;
							physics.grid[myX - 1][myY + 1] = 3;
						}
						// Right
						else if (physics.grid[myX + 1][myY] < 1 && myX > 0 && myX < physics.GRID_WIDTH)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosX += 4;
							physics.grid[myX + 1][myY] = 3;
						}
						// Left
						else if (physics.grid[myX - 1][myY] < 1 && myX > 0 && myX < physics.GRID_WIDTH)
						{
							physics.grid[myX][myY] = 0;
							obj->mPosX -= 4;
							physics.grid[myX - 1][myY] = 3;
						}
					}
				}
			}
			if (index == 3)
			{
				// Smoke simulation
				if (obj->type == ObjectType::Smoke && obj->isRenderable)
				{
					if (obj->mPosY > 0)
					{
						obj->mPosY -= 4;
					}
					else
					{
						obj->isRenderable = false;
						obj->~Object();
					}
				}
			}
		}

		if (SDL_mutexV(physics.mut[index]) == -1)
		{
			fprintf(stderr, "Couldn't unlock mutex\n");
			exit(-1);
		}
	}
	return 0;
}

PhysicsManager::PhysicsManager()
{
	for (int i = 0; i < threadNum; i++)
	{
		mut.push_back(SDL_CreateMutex());
	}
	for (int i = 0; i < threadNum; i++)
	{
		threadData[i] = i;
		threads.push_back(SDL_CreateThread(threadFunction, "Thread", (void*)threadData[i]));
	}
}

float PhysicsManager::Lerp(float a, float b, float x)
{
	return (a * (1.0 - x)) + (b * x);
}

void PhysicsManager::SendCollisionNotification() {}

int PhysicsManager::SpawnParticles(ObjectType type, Texture* tex, int x, int y, int size)
{
	switch (size)
	{
		case 4:
			ObjectManager::GetInstance().objects.push_back(new Object(x, y, type, tex));
			ObjectManager::GetInstance().objects.push_back(new Object(x + 4, y, type, tex));
			ObjectManager::GetInstance().objects.push_back(new Object(x, y + 4, type, tex));
			ObjectManager::GetInstance().objects.push_back(new Object(x + 4, y + 4, type, tex));
			particleCounter += 4;
			physicsStarted = true;

			break;
		case 16:
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					ObjectManager::GetInstance().objects.push_back(new Object(x + (4 * j), y + (4 * i), type, tex));
				}
			}
			physicsStarted = true;
			particleCounter += 16;
			break;
		case 32:
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					ObjectManager::GetInstance().objects.push_back(new Object(x + (4 * j), y + (4 * i), type, tex));
				}
			}
			break;
		default:
			ObjectManager::GetInstance().objects.push_back(new Object(x, y, type, tex));
			physicsStarted = true;
			particleCounter++;
			break;
		}
	return size;
}

void PhysicsManager::InitializeMatrix()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			grid[j][i] = 0;
		}
	}
}

void PhysicsManager::Update(void) {}

int PhysicsManager::RoundUp(int numToRound, int multiple)
{
	if (multiple == 0)
		return numToRound;

	int remainder = numToRound % multiple;
	if (remainder == 0)
		return numToRound;

	return numToRound + multiple - remainder;
}