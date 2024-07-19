#ifndef API_GAMEPLAY_HOUSE_H_
#define API_GAMEPLAY_HOUSE_H_

#include "building.h"

class House : public Building {

public:
	House(float x, float y);

protected:
	void DefineTexture() override;

};

#endif
