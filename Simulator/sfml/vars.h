#pragma once
#include "imgui/imgui.h"

//global variables
namespace vars {
	//deltatime in milliseconds
	extern float deltaTime;

	//sim settings
	extern float g_simSpeed;
	extern float g_gravityf;

	namespace colorTheme {
		extern ImColor dark_gray;                         
		extern ImColor gray; 
		extern ImColor light_gray;                       
		extern ImColor light_blue;
		extern ImColor lighter_black;
	}
}