#pragma once
#include "Singleton.h"
#include "SDL.h"
#include "Object.h"
#include <vector>

class ObjectManager : public Singleton<ObjectManager>
{
	friend class Singleton<ObjectManager>;

private:
	bool collision;
	ObjectManager();
	~ObjectManager();

public:
	std::vector<Object*> objects;
	bool IsColliding();
	void Update(void);
};