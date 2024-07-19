#include "gameplay/mill.h"


#include "resources/ResourcesManager.h"

Mill::Mill(float x, float y) : Building(x,y)
{
	DefineTexture();
}

void Mill::DefineTexture()
{
	shape_.setTexture(ResourcesManager::Get().GetTexture(ResourcesManager::Resource::kStoneHouse));
}
