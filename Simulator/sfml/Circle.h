#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <SFML/Graphics.hpp>

class Circle {
private:
	void init();
public:
	Circle() {
		init();
	}

	void update_position(Circle& circle,std::vector<Circle>& circles, float simSpeed);

	//set color of object of rgb channels and divide it by 255
	void setColor(float r, float g, float b);

	//object
	sf::CircleShape circle;

	//get and set object name
	std::string name = "circle";

	//check if object is active or inactive
	//bool isActive = false;

	//object mass
	float mass = 5.f;
	
	//object gravity pull (later)
	//bool emitgravity = false;

	//object color
	float circleColor[3] = { 255.f / 255, 0.f / 255, 0.f / 255 };

	//object position
	float posx = 0, posy = 0;

	//amount of segments object is made off
	int circleSegments;

	//object radius
	float radius = 20;

	//check if we want to render object on window
	bool active = false;

	//current object velocity
	float velx = 0, vely = 0;
};