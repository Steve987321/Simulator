#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <SFML/Graphics.hpp>

class Circle {
public:
	Circle();

	Circle(std::string Name, int X, int Y, int Mass) : name(Name), posx(X), posy(Y), mass(Mass) {}
	
	void update_position(const std::vector<Circle>& circles, float simSpeed);

	void setColor(float r, float g, float b);

	// sfml circleshape object
	sf::CircleShape circle;

	std::string name = "circle";

	float mass = 5.f;

	float circleColor[3] = { 255.f / 255, 0.f / 255, 0.f / 255 };

	float posx = 0, posy = 0;

	float radius = 20;
	
	float velx = 0, vely = 0;
	
	//amount of segments object is made off
	int circleSegments = 10;

	//check if we want to render object on window
	bool isActive = true;
};