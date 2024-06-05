#pragma once
#include "Singleton.h"
#include "SDL.h"

class SoundManager : public Singleton<SoundManager>
{
	friend class Singleton<SoundManager>;

private:
	float volume;
	SoundManager() {};

public:
	void Update(void);
	void LoadSound();
};