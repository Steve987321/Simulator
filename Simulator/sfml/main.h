#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace toad {
	namespace info {
		extern char title[] = "Toad Simulations";
		extern int window_sizeX = 1000;
		extern int window_sizeY = 800;
	}

	//global physics behaviour
	namespace physics {
		extern bool gravity = false;
		extern float gravityf = 9.89f;
		extern float groundmass = 5.f;
	}
}