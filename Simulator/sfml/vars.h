#pragma once
#include "imgui/imgui.h"
#include <vector>
#include "Circle.h"

//global variables
namespace vars {
	//deltatime in milliseconds
	inline float deltaTime = 0.f;

	//sim settings
	inline float g_simSpeed = 2000;
	inline const float g_gravityf = 6.6742E-11;

	inline std::vector<Circle> circles;

	namespace colorTheme
	{
		inline ImColor dark_gray = ImColor(21, 21, 21);
		inline ImColor gray = ImColor(36, 36, 36);
		inline ImColor light_gray = ImColor(46, 46, 46);
		inline ImColor light_blue = ImColor(48, 173, 228);
		inline ImColor lighter_black = ImColor(26, 26, 26);
	}
}