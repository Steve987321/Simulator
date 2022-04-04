#include "toadsim.h"

std::string toadsim::char_to_string(char chr[])
{
	std::string s(chr);
	return s;
}

inline float gameObject::dist(sf::Vector2f pos1, sf::Vector2f pos2)
{
	return std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));
}
