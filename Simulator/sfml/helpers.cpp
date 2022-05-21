#include "helpers.h"


std::string toad::char_to_string(const char* chr)
{
	return std::string (chr);
}

float toad::dist(sf::Vector2f pos1, sf::Vector2f pos2)
{
	return std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));
}

//TODO: fix dis bug
//when size = 1 and name of circle is circle2 there are 2 objects wit same name results in glithch
void toad::add_object(std::vector<Circle>& circles)
{
	circles.push_back(Circle::Circle());
	circles[circles.size() - 1].name = "circle" + std::to_string(circles.size());
	circles[circles.size() - 1].setColor(255, 255, 255);
}

void toad::delete_object(std::vector<Circle>& circles, int& element)
{
	//check if atleast 2 elements
	//if (circles.size() > 1) circles.erase(circles.begin() + element ); 
	if (circles.size() > 1) {
		circles.erase(circles.begin() + (element));
		element = 0;
	}
}
