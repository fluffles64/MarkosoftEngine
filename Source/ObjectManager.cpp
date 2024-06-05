#include "ObjectManager.h"

void ObjectManager::Update(void) {}

ObjectManager::ObjectManager()
{
	objects = std::vector<Object*>();
	// Reserve objects depending on screen width * height
	objects.reserve(2073600);
}

ObjectManager::~ObjectManager() {}

bool ObjectManager::IsColliding()
{
	return this->collision;
}