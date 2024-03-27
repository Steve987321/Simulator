#pragma once
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Circle.h"

//functions for ui
namespace toad
{
	/// <returns>the distance between two vectors in pixels</returns>
    float dist(sf::Vector2f pos1, sf::Vector2f pos2);

	void add_object(std::vector<Circle>& circles);

	void delete_object(std::vector<Circle>& circles, int& element);

	std::string char_to_string(const char* chr);
}