#include "gameplay/house.h"


#include "resources/ResourcesManager.h"

House::House(float x, float y) : Building(x,y)
{
	DefineTexture();
}

void House::DefineTexture()
{
	shape_.setTexture(ResourcesManager::Get().GetTexture(ResourcesManager::Resource::kStoneHouse));
}
