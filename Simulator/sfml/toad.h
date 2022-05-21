#pragma once

#include "ui.h"
#include "main.h"
#include "Circle.h"
#include "Physics.h"
#include "helpers.h"
#include "vars.h"
#include "logger.h"

namespace toad
{
	/// <summary>
	/// the	main loop of the simulator.
	/// </summary>
	void run();

	/// <summary>
	/// initialize the simulator.
	/// </summary>
	/// <returns>if the simulator has successfully initialized. </returns>
	bool init();

	/// <summary>
	/// shut down.
	/// </summary>
	void clean_up();

	/// <summary>
	/// Update variables of positions
	/// </summary>
	void onUpdate();

	/// <summary>
	/// Rendering UI and SFML objects.
	/// </summary>
	void onRender();

	/// <summary>
	/// handles events inputted from the user.
	/// </summary>
	void event_handler();
}
