#pragma once
#include <SFML/Graphics.hpp>

namespace ui
{
	inline char objectName[16] = "circle1";
	inline int itemInspecting = 0;
	inline bool object_creation_menu = false;
	inline sf::Vector2i cursorpos;
	
	void decorations();
	void render_ui();
}

