#pragma once
#include "Singleton.h"
#include "SDL.h"

class InputManager : public Singleton<InputManager>
{
	friend class Singleton<InputManager>;

private:
	// Top left position
	SDL_Point mPosition;

	// Keyboard state
	const Uint8* mCurrentKeyStates;

	// Private constructor to avoid more than one instance
	InputManager() {};

public:
	void Update(void);
	bool GetKey(int scanCode);
};