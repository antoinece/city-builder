#ifndef API_PATHFINDING_PATH_H_
#define API_PATHFINDING_PATH_H_
#include <queue>
#include <SFML/System/Vector2.hpp>

class Path
{

private:
	std::queue<sf::Vector2f> steps_;
	sf::Vector2f next_step_;
	sf::Vector2f final_destination_;

	bool is_available_ = false;
	// TODO : async calculation (job system)
	bool is_ready_ = true;

public:
	bool IsEnded() const;
	bool IsAvailable() const;
	bool IsReady() const;
	sf::Vector2f FinalDestination() const;

	sf::Vector2f GetNextStep();
	void SetSteps(std::vector<sf::Vector2f> steps);

	// steps getter
	const std::queue<sf::Vector2f>& GetSteps();


};
#endif


