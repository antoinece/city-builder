
#ifndef CORE_MATHS_SFML_VEC2F_H_
#define CORE_MATHS_SFML_VEC2F_H_

#include "cmath"
#include <SFML/System/Vector2.hpp>

[[nodiscard]] inline float squaredMagnitude(sf::Vector2f v)
{
	return  (v.x * v.x + v.y * v.y);
}

[[nodiscard]] inline float Magnitude(sf::Vector2f v)
{
	return  std::sqrt(squaredMagnitude(v));
}



[[nodiscard]] inline sf::Vector2f Normalized(sf::Vector2f v)
{

	// IF/ELSE Style
	float norm_x = 0;
	if (v.x == 0) {
		norm_x = 0;
	}
	else {
		norm_x = v.x / Magnitude(v);
	}

	// Ternary style
	float norm_y = v.y == 0 ? 0 : v.y / Magnitude(v);

	return { norm_x, norm_y };

}

#endif
