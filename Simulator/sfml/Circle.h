#pragma once
#include "main.h"

class Circle {
public:
	Circle(std::string Name) {
		name = Name;
	}
	//object name
	std::string name;

	//ImGui inspecting object
	bool inspecting = false;

	//object mass
	float mass = 5.f;
	
	//object gravity pull (later)
	//bool emitgravity = false;

	float circleColor[3] = { 255.f / 255, 0.f / 255, 0.f / 255 };

	//object position
	float posx = 0, posy = 0;

	//amount of segments object is made off
	int circleSegments;

	float circleScaleX = 0.5, circleScaleY = 0.5;
};