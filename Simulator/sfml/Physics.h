#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "toadsim.h"

class physics {
public:
	//calculate the velocity of an object
	static inline float calc_gravity_velocity(float object_mass, float dist, float gravity) {
		return gravity * (object_mass / dist);
	}
	static inline float calc_gravity_velocity(float object_mass, float dist, float gravity, float object_mass2) {
		return gravity * (object_mass * object_mass2 / dist);
	}
	static inline float calc_gravity_velocity(sf::Vector2f pos1, sf::Vector2f pos2, float mass1, float mass2, float gravity) {
		return gravity * (mass1 * mass2 / gameObject::dist(pos1, pos2));
	}
};

