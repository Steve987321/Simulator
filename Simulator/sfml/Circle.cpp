#include "vars.h"
#include "Physics.h"

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

void Circle::update_position(Circle& circle, std::vector<Circle>& circles, float simSpeed)
{
	float total_vx = 0, total_vy = 0;
	for (Circle ci : circles) {
		if (circle.name == ci.name) {
			continue;
		}
		sf::Vector2f vel = physics::calc_gravity_velocity_vec(circle, ci);
		
		total_vx += vel.x;
		total_vy += vel.y;

		circle.velx += total_vx / circle.mass * simSpeed;
		circle.vely += total_vy / circle.mass * simSpeed;

		this->posx += this->velx * simSpeed;
		this->posy += this->vely * simSpeed;

		this->circle.setPosition(this->posx, this->posy);
	}
}

void Circle::setColor(float r, float g, float b)
{
	circleColor[0] = r / 255.f;
	circleColor[1] = g / 255.f;
	circleColor[2] = b / 255.f;
}
