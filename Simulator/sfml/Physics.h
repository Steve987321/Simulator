#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "helpers.h"
#include "vars.h"

namespace toad{

namespace physics
{
	inline sf::Vector2f calc_gravity_velocity_vec(const Circle& circle, const Circle& other) {
		float distance_x = other.circle.getPosition().x - circle.circle.getPosition().x;
		float distance_y = other.circle.getPosition().y - circle.circle.getPosition().y;
		 
		float force = vars::g_gravityf * (circle.mass * other.mass / std::pow(toad::dist(circle.circle.getPosition(), other.circle.getPosition()), 2));
		
		//get angle
		float theta = std::atan2(distance_y, distance_x);
		
		float force_x = std::cos(theta) * force;
		float force_y = std::sin(theta) * force;

		return sf::Vector2f(force_x, force_y);
	}
}

}
