#include "Circle.h"

//init circle
void Circle::init()
{
	circle.setRadius(radius);
	//sfml bug???
	//circle.setFillColor(sf::Color::Red);
	circle.setOutlineColor(sf::Color::Black);
	circle.setScale(sf::Vector2f(0.5, 0.5));
	circle.setPosition(sf::Vector2f(10, 10));
	circleSegments = circle.getPointCount();
}

void Circle::setColor(float r, float g, float b)
{
	circleColor[0] = r / 255.f;
	circleColor[1] = g / 255.f;
	circleColor[2] = b / 255.f;
}
