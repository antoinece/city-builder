#ifndef API_GAMEPLAY_MILL_H_
#define API_GAMEPLAY_MILL_H_

#include "building.h"

class Mill : public Building {

public:
	Mill(float x, float y);

protected:
	void DefineTexture() override;

};

#endif
