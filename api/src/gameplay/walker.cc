#include "gameplay/walker.h"

#include <iostream>

#include "sfml_vec2f.h"


Walker::Walker(float x, float y, float linear_speed) : SpriteEntity(x, y)
{
	setPosition(x, y);
	linear_speed_ = linear_speed;
	last_time_ = std::chrono::steady_clock::now();

	destination_ = sf::Vector2f(x, y);

}

void Walker::set_destination(float x, float y)
{
	destination_.x = x;
	destination_.y = y;
}

void Walker::set_linear_speed(float linear_speed)
{
	linear_speed_ = linear_speed;
}

void Walker::set_path(const Path path)
{
	if (path.IsAvailable() && path.IsReady())
	{
		path_ = path;
	}
}

void Walker::Tick()
{
	// Delta Time ----------------
	const auto now{ std::chrono::steady_clock::now() };
	const std::chrono::duration<float> elapsed_seconds{ now - last_time_ };
	last_time_ = std::chrono::steady_clock::now();

	if (path_.IsEnded())
	{
		//std::cout << "Path finished" << std::endl;
	}

	if (path_.IsAvailable())
	{
		// Positionning -------------------------------
		const sf::Vector2f actual_position = getPosition();
		const sf::Vector2f direction = Normalized(destination_ - actual_position);
		sf::Vector2f new_position = sf::Vector2f(0, 0);

		if (Magnitude(destination_ - actual_position) < 0.01f * 64)
		{
			//std::cout << "Step reached" << std::endl;
			new_position = destination_;
			destination_ = path_.GetNextStep();

		}
		else
		{
			new_position = actual_position + sf::Vector2f(
				direction.x * linear_speed_ * elapsed_seconds.count(),
				direction.y * linear_speed_ * elapsed_seconds.count()
			);

			//std::cout << "Position [" << new_position.x << ":" << new_position.y << "]" << std::endl;

		}

		// Update positions ---------------------------
		setPosition(new_position);
		shape_.setPosition(new_position);
		rect_.setPosition(new_position);

	}
	else
	{
		//std::cout << "No path available" << std::endl;
	}



}

sf::Vector2f Walker::LastDestination() const
{
	return destination_;
}


