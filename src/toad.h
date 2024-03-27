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
	void run(sf::RenderWindow& window);

	/// <summary>
	/// initialize the simulator.
	/// </summary>
	/// <returns>if the simulator has successfully initialized. </returns>
	bool init(sf::RenderWindow& window);

	/// <summary>
	/// shut down.
	/// </summary>
	void clean_up(sf::RenderWindow& window);

	/// <summary>
	/// Update variables.
	/// </summary>
	void onUpdate(sf::RenderWindow& window);

	/// <summary>
	/// Rendering UI and SFML objects.
	/// </summary>
	void onRender(sf::RenderWindow& window);

	/// <summary>
	/// handles events inputted from the user and window events.
	/// </summary>
	void event_handler(sf::RenderWindow& window);
}
