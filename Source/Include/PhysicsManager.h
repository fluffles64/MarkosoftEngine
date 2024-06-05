#pragma once
#include "Singleton.h"
#include "SDL.h"
#include "Object.h"
#include "ObjectManager.h"
#include <SDL_thread.h>
#include <vector>
#include <stdio.h>
#include <string>

class PhysicsManager : public Singleton<PhysicsManager>
{
	friend class Singleton<PhysicsManager>;

private:
	float a;
	float b;
	float x;
	float gravity;
	float vel;
	float accel;
	int threadNum = 4;
	int rows = GraphicManager::GetInstance().SCREEN_HEIGHT / 4;
	int columns = GraphicManager::GetInstance().SCREEN_WIDTH / 4;
	std::vector<int> threadData = std::vector<int>(threadNum);
	std::vector<SDL_Thread*> threads = std::vector<SDL_Thread*>();

	PhysicsManager();

public:
	std::vector<SDL_mutex*> mut = std::vector<SDL_mutex*>();
	bool physicsStarted = false;
	int particleCounter = 0;
	bool spawnSmoke = false;
	int mat[480][270];
	int SpawnParticles(std::string objPath, int x, int y, int size);
	void InitializeMatrix();
	void SimulateParticles();
	int RoundUp(int numToRound, int multiple);
	float Lerp(float a, float b, float x);
	void SendCollisionNotification();
	void Update(void);
};