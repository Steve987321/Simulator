#pragma once
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Circle.h"

//functions for ui
class toadsim {
public: 
	//char to string conversion
	static std::string char_to_string(char chr[]);
};

class gameObject {
public:
	//gets distance between 2 objects in pixels
	static inline float dist(sf::Vector2f pos1, sf::Vector2f pos2) {
		return std::sqrt(std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2));
	}

	//adds an object
	static void add_object(std::vector<Circle>& circles);

	//delete an object
	static void delete_object(std::vector<Circle>& circles,int& element);
};
