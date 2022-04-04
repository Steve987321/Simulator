#pragma once

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

class toadsim {
public: 
	//char to string conversion
	static std::string char_to_string(char chr[]);
};

class gameObject {
public:
	//gets distance between 2 objects in pixels
	static inline float dist(sf::Vector2f pos1, sf::Vector2f pos2);
};
