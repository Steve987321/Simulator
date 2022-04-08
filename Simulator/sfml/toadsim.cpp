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

void gameObject::add_object(std::vector<Circle>& circles)
{
	circles.push_back(Circle::Circle());
	circles[circles.size() - 1].name = "circle" + std::to_string(circles.size());
	circles[circles.size() - 1].setColor(255, 255, 255);
}

void gameObject::delete_object(std::vector<Circle>& circles, int& element)
{
	//check if atleast 2 elements
	if (circles.size() > 1) {
		std::cout << circles.size() << std::endl;
		circles.erase(circles.begin() + (element));
		element = 0;
	}
}
