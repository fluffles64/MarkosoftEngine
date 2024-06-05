#include "PhysicsManager.h"

int threadFunction(void* data)
{
	int index = (int)data;
	// Main loop flag
	bool quit = false;
	while (!quit)
	{
		if (SDL_mutexP(PhysicsManager::GetInstance().mut[index]) == -1)
		{
			fprintf(stderr, "Couldn't lock mutex\n");
			exit(-1);
		}
			
		for (int i = 0; i < ObjectManager::GetInstance().objects.size(); i++)
		{
			//// Check if the object has settled
			//Object* obj = ObjectManager::GetInstance().objects[i];
			//if (obj->Settled)
			//{
			//	continue; // Skip the calculation for settled objects
			//}

			int myX = ObjectManager::GetInstance().objects[i]->mPosX / 4;
			int myY = ObjectManager::GetInstance().objects[i]->mPosY / 4;

			if (index == 0) {
				// Sand simulation
				if (ObjectManager::GetInstance().objects[i]->objPath == "../../media/sand.png")
				{
					if (myY < 270 && myY >= 0 && myX < 480 && myX >= 0) {
						if (PhysicsManager::GetInstance().mat[myX][myY + 1] < 1)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosY += 4;
							PhysicsManager::GetInstance().mat[myX][myY + 1] = 1;
						}
						else if (PhysicsManager::GetInstance().mat[myX][myY + 1] == 2)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosY += 4;
							PhysicsManager::GetInstance().mat[myX][myY + 1] = 1;
						}
						else if (PhysicsManager::GetInstance().mat[myX + 1][myY + 1] < 1 && myX > 0)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosX += 4;
							ObjectManager::GetInstance().objects[i]->mPosY += 4;
							PhysicsManager::GetInstance().mat[myX + 1][myY + 1] = 1;
						}
						else if (PhysicsManager::GetInstance().mat[myX - 1][myY + 1] < 1 && myX > 0)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosX -= 4;
							ObjectManager::GetInstance().objects[i]->mPosY += 4;
							PhysicsManager::GetInstance().mat[myX - 1][myY + 1] = 1;
						}
					}
				}
			}

			if (index == 1)
			{
				// Water simulation
				if (ObjectManager::GetInstance().objects[i]->objPath == "../../media/water.png" && ObjectManager::GetInstance().objects[i]->isRenderable)
				{
					if (myY < 270 && myY >= 0 && myX < 480 && myX >= 0)
					{

						// Down
						if (PhysicsManager::GetInstance().mat[myX][myY + 1] < 1)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosY += 4;
							PhysicsManager::GetInstance().mat[myX][myY + 1] = 2;
						}
						// Sand interaction
						/*else if (PhysicsManager::GetInstance().mat[myX][myY - 1] == 1) {
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosY -= 4;
							PhysicsManager::GetInstance().mat[myX][myY - 1] = 2;
							// ObjectManager::GetInstance().objects[i]->isRenderable = false;
							// ObjectManager::GetInstance().objects[i]->~Object();
						}*/
						// Down Right
						else if (PhysicsManager::GetInstance().mat[myX + 1][myY + 1] < 1 && myX > 0 && myX < 480)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosX += 4;
							ObjectManager::GetInstance().objects[i]->mPosY += 4;
							PhysicsManager::GetInstance().mat[myX + 1][myY + 1] = 2;
						}
						// Down left
						else if (PhysicsManager::GetInstance().mat[myX - 1][myY + 1] < 1 && myX > 0 && myX < 480)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosX -= 4;
							ObjectManager::GetInstance().objects[i]->mPosY += 4;
							PhysicsManager::GetInstance().mat[myX - 1][myY + 1] = 2;
						}
						// Right
						else if (PhysicsManager::GetInstance().mat[myX + 1][myY] < 1 && myX > 0 && myX < 480)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosX += 4;
							PhysicsManager::GetInstance().mat[myX + 1][myY] = 2;
						}
						// Left
						else if (PhysicsManager::GetInstance().mat[myX - 1][myY] < 1 && myX > 0 && myX < 480)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosX -= 4;
							PhysicsManager::GetInstance().mat[myX - 1][myY] = 2;
						}
					}
				}
			}

			if (index == 2)
			{
				// Wood simulation
				if (myY < 270 && myY >= 0 && myX < 480 && myX >= 0) {
					if (ObjectManager::GetInstance().objects[i]->objPath == "../../media/wood.png" && ObjectManager::GetInstance().objects[i]->isRenderable)
					{
						if (myY < 270 && myY >= 0 && myX < 480 && myX >= 0)
						{
							if (PhysicsManager::GetInstance().mat[myX][myY] < 1)
							{
								PhysicsManager::GetInstance().mat[myX][myY] = 4;
							}
							else if (PhysicsManager::GetInstance().mat[myX][myY - 1] == 3)
							{
								PhysicsManager::GetInstance().mat[myX][myY] = 0;
								ObjectManager::GetInstance().objects[i]->isRenderable = false;
								ObjectManager::GetInstance().objects[i]->~Object();
							}
						}
					}
					// Lava simulation
					if (ObjectManager::GetInstance().objects[i]->objPath == "../../media/lava.png" && ObjectManager::GetInstance().objects[i]->isRenderable)
					{
						// Down
						if (PhysicsManager::GetInstance().mat[myX][myY + 1] < 1)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosY += 4;
							PhysicsManager::GetInstance().mat[myX][myY + 1] = 3;
						}
						// Down Right
						else if (PhysicsManager::GetInstance().mat[myX + 1][myY + 1] < 1 && myX > 0 && myX < 480)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosX += 4;
							ObjectManager::GetInstance().objects[i]->mPosY += 4;
							PhysicsManager::GetInstance().mat[myX + 1][myY + 1] = 3;
						}
						// Down left
						else if (PhysicsManager::GetInstance().mat[myX - 1][myY + 1] < 1 && myX > 0 && myX < 480)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosX -= 4;
							ObjectManager::GetInstance().objects[i]->mPosY += 4;
							PhysicsManager::GetInstance().mat[myX - 1][myY + 1] = 3;
						}
						// Right
						else if (PhysicsManager::GetInstance().mat[myX + 1][myY] < 1 && myX > 0 && myX < 480)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosX += 4;
							PhysicsManager::GetInstance().mat[myX + 1][myY] = 3;
						}
						// Left
						else if (PhysicsManager::GetInstance().mat[myX - 1][myY] < 1 && myX > 0 && myX < 480)
						{
							PhysicsManager::GetInstance().mat[myX][myY] = 0;
							ObjectManager::GetInstance().objects[i]->mPosX -= 4;
							PhysicsManager::GetInstance().mat[myX - 1][myY] = 3;
						}
					}
				}
			}
			if (index == 3) {
				// Smoke simulation
				if (ObjectManager::GetInstance().objects[i]->objPath == "../../media/smoke.png" && ObjectManager::GetInstance().objects[i]->isRenderable)
				{
					if (ObjectManager::GetInstance().objects[i]->mPosY > 0)
					{
						ObjectManager::GetInstance().objects[i]->mPosY -= 4;
					}
					else
					{
						ObjectManager::GetInstance().objects[i]->isRenderable = false;
						ObjectManager::GetInstance().objects[i]->~Object();
					}
				}
			}
		}	
		// printf("\nGraphic Thread counter: %d", index);
		// SDL_Delay(1);

		if (SDL_mutexV(PhysicsManager::GetInstance().mut[index]) == -1)
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

int PhysicsManager::SpawnParticles(std::string objPath, int x, int y, int size)
{
	switch (size)
	{
		case 4:
			ObjectManager::GetInstance().objects.push_back(new Object(x, y, objPath));
			ObjectManager::GetInstance().objects.push_back(new Object(x + 4, y, objPath));
			ObjectManager::GetInstance().objects.push_back(new Object(x, y + 4, objPath));
			ObjectManager::GetInstance().objects.push_back(new Object(x + 4, y + 4, objPath));
			particleCounter += 4;
			physicsStarted = true;

			break;
		case 16:
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					ObjectManager::GetInstance().objects.push_back(new Object(x + (4 * j), y + (4 * i), objPath));
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
					ObjectManager::GetInstance().objects.push_back(new Object(x + (4 * j), y + (4 * i), objPath));
				}
			}
			break;
		default:
			ObjectManager::GetInstance().objects.push_back(new Object(x, y, objPath));
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
			mat[j][i] = 0;
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