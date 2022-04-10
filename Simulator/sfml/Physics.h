#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "toadsim.h"
#include "vars.h"

class physics {
public:
	//calculate the velocity of an object
	static inline float calc_gravity_velocity(float object_mass, float dist) {
		return vars::gravityf * (object_mass / dist);
	}
	static inline float calc_gravity_velocity(float object_mass, float dist, float object_mass2) {
		return vars::gravityf * (object_mass * object_mass2 / dist);
	}
	static inline float calc_gravity_velocity(sf::Vector2f pos1, sf::Vector2f pos2, float mass1, float mass2) {		
		return vars::gravityf * (mass1 * mass2 / gameObject::dist(pos1, pos2));
	}
	static inline sf::Vector2f calc_gravity_velocity_vec(Circle circle, Circle other) {
		float distance_x = other.circle.getPosition().x - circle.circle.getPosition().x;
		float distance_y = other.circle.getPosition().y - circle.circle.getPosition().y;

		float force = vars::gravityf * (circle.mass * other.mass / std::pow(gameObject::dist(circle.circle.getPosition(), other.circle.getPosition()), 2));
		
		//get angle
		float theta = std::atan2(distance_y, distance_x);
		
		float force_x = std::cos(theta) * force;
		float force_y = std::sin(theta) * force;

		return sf::Vector2f(force_x, force_y);
	}
};

