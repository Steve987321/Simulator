#pragma once

class physics {
public:
	//calculate the velocity of an object!
	static inline float calc_gravity_velocity(float object_mass, float dist, float gravity) {
		float vel = gravity * (object_mass / dist);
		return vel;
	}
	static inline float calc_gravity_velocity(float object_mass, float dist, float gravity, float object_mass2) {
		float vel = gravity * (object_mass * object_mass2/ dist);
		return vel;
	}

};