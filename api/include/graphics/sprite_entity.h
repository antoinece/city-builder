#ifndef API_GRAPHICS_SPRITE_ENTITY_H
#define API_GRAPHICS_SPRITE_ENTITY_H

#include <SFML/Graphics/Sprite.hpp>

#include "resources/ResourcesManager.h"

class SpriteEntity : public sf::Drawable {

public:
	SpriteEntity(float x, float y);

protected:
	sf::Sprite shape_;
	sf::RectangleShape rect_;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void DefineTexture() = 0;

};

#endif
