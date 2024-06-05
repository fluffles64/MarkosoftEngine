#include "InputManager.h"

void InputManager::Update(void)
{
	mCurrentKeyStates = SDL_GetKeyboardState(NULL);
}

bool InputManager::GetKey(int scanCode)
{
	return mCurrentKeyStates[scanCode] != 0;
}