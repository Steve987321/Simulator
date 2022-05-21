#include "vars.h"
#include "Physics.h"

Circle::Circle() 
{
	circle.setRadius(radius);
	//sfml bug???
	//circle.setFillColor(sf::Color::Red);
	circle.setOutlineColor(sf::Color::Black);
	circle.setScale(sf::Vector2f(0.5, 0.5));
	circle.setPosition(sf::Vector2f(10, 10));
	circleSegments = circle.getPointCount();
}

void Circle::update_position(std::vector<Circle>& circles, float simSpeed)
{
	float total_vx = 0, total_vy = 0;
	for (Circle other : circles) {
		if (this->name == other.name || !this->isActive || !other.isActive) continue;
		sf::Vector2f vel = physics::calc_gravity_velocity_vec(*this, other);
		
		total_vx += vel.x;
		total_vy += vel.y;

		this->velx += total_vx / this->mass * simSpeed;
		this->vely += total_vy / this->mass * simSpeed;

		this->posx += this->velx * simSpeed;
		this->posy += this->vely * simSpeed;

		this->circle.setPosition(this->posx, this->posy);
	}
}

void Circle::setColor(float r, float g, float b)
{ 
	this->circleColor[0] = r / 255.f;
	this->circleColor[1] = g / 255.f;
	this->circleColor[2] = b / 255.f;
}
