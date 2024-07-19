#ifndef API_GAMEPLAY_BUILDING_H
#define API_GAMEPLAY_BUILDING_H

#include "graphics/sprite_entity.h"

class Building : public SpriteEntity {

public:
	Building(float x, float y) : SpriteEntity(x,y)
	{
		
	}

protected:
	void DefineTexture() override;

};


#endif // BUILDING_H
