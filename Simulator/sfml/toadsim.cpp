#include "toadsim.h"

std::string toadsim::char_to_string(char chr[])
{
	std::string s(chr);
	return s;
}

//TODO: fix dis bug
//when size = 1 and name of circle is circle2 there are 2 objects wit same name
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
		circles.erase(circles.begin() + (element));
		element = 0;
	}
}
