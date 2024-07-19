#ifndef API_GAMEPLAY_WALKER_H
#define API_GAMEPLAY_WALKER_H

#include <chrono>
#include <SFML/Graphics/Transformable.hpp>

#include "graphics/sprite_entity.h"
#include "pathfinding/path.h"

class Walker : public sf::Transformable, public SpriteEntity
{
	// 1 : Destination
	// 2 : Framerate independant
	// 3 : Close to steering behaviour

private:
	float linear_speed_ = 0;
	sf::Vector2f destination_;
	std::chrono::time_point<std::chrono::steady_clock> last_time_;

protected:
	Path path_;

public:
	Walker(float x, float y, float linear_speed);

	void set_destination(float x, float y);
	void set_linear_speed(float linear_speed);
	void set_path(const Path path);

	void Tick();
	sf::Vector2f LastDestination() const;

};

#endif
