#include "ObjectManager.h"

void ObjectManager::Update(void) {}

ObjectManager::ObjectManager()
{
	objects = std::vector<Object*>();
	objects.reserve(1000000);
}

ObjectManager::~ObjectManager() {}

bool ObjectManager::IsColliding()
{
	return this->collision;
}