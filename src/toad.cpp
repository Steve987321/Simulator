#include "toad.h"

sf::Clock deltaClock;
sf::Time dt;

using namespace toad;

bool init_window(sf::RenderWindow& window)
{
	window.create(sf::VideoMode(toad::info::window_sizeX, toad::info::window_sizeY), toad::info::title, sf::Style::Titlebar | sf::Style::Close);

	window.setFramerateLimit(60);

	return (ImGui::SFML::Init(window));
}

/// <summary>
/// adds 2 circles, one with velocity and different mass 
/// </summary>
void load_default_scene()
{

	//TODO: make it file based
	
	vars::circles.emplace_back();
	vars::circles.emplace_back();
	vars::circles[0].name = "circle1";
	vars::circles[0].setColor(255, 255, 255);
	vars::circles[0].isActive = true;
	vars::circles[0].circle.setPosition(200, 150);
	vars::circles[0].velx = 0.00001f;

	vars::circles[1].name = "circle2";
	vars::circles[1].setColor(255, 255, 255);
	vars::circles[1].isActive = true;
	vars::circles[1].circle.setPosition(200, 200);
	vars::circles[1].mass = 100;
	
}

void render_window_objects(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);

	//
	//--------------------draw here------------------------//
	//

	for (Circle& ci : vars::circles)
		if (ci.isActive) 
			window.draw(ci.circle);

	//draw imgui
	ImGui::SFML::Render(window);
	
	//
	//--------------------draw here-------------------------//
	//

	window.display();
}

/// <summary>
/// initializes window and object scene.
/// </summary>
/// <returns>Wether it has successfully initialized the window </returns>
bool toad::init(sf::RenderWindow& window)
{
	log_debug("Initializing circles");

	//add 2 circles to scene on start 
	//TODO: Make it file based
	load_default_scene();
	
	log_ok("Initialized objects");

	log_debug("Initializing window");

	//init sfml window
	if (init_window(window)) { log_ok("Initialized window"); return true; }
	else return false;
}

void toad::run(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		toad::onUpdate(window);
		toad::onRender(window);
	}
	toad::clean_up(window);
}

void toad::clean_up(sf::RenderWindow& window)
{
	ImGui::SFML::Shutdown();
	window.close();
}

/// <summary>
///render objects and ui. 
/// </summary>
void toad::onRender(sf::RenderWindow& window)
{
	ui::render_ui();
	render_window_objects(window);
}

void toad::onUpdate(sf::RenderWindow& window)
{
	toad::event_handler(window);
	
	//options to update live
	static bool once = false;
	if (!once) {
		once = true;
	}
	else {
		vars::circles[ui::itemInspecting].circle.setPosition(sf::Vector2f(vars::circles[ui::itemInspecting].posx, vars::circles[ui::itemInspecting].posy));
		vars::circles[ui::itemInspecting].circle.setFillColor(sf::Color(vars::circles[ui::itemInspecting].circleColor[ui::itemInspecting] * 255, vars::circles[ui::itemInspecting].circleColor[1] * 255, vars::circles[ui::itemInspecting].circleColor[2] * 255));
	}

	//apply pos data to real pos on screen
	for (int i = 0; i < vars::circles.size(); i++) {
		vars::circles[i].posx = vars::circles[i].circle.getPosition().x;
		vars::circles[i].posy = vars::circles[i].circle.getPosition().y;
	}

	//update deltatime
	dt = deltaClock.restart();
	vars::deltaTime = dt.asSeconds();

	//update pos 
	for (Circle& ci : vars::circles) 
	{
		ci.update_position(vars::circles, vars::g_simSpeed * 1000 * vars::deltaTime);
	}

	ImGui::SFML::Update(window, dt);
}

void toad::event_handler(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event)) {
		//events
		ImGui::SFML::ProcessEvent(event);

		//mouse button events
		if (event.type == sf::Event::MouseButtonPressed) 
		{
			if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) 
			{
				//lmb
				if (event.mouseButton.button == sf::Mouse::Left) {
					for (int i = 0; i < vars::circles.size(); i++)
						if (vars::circles[i].circle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
						{
							strncpy(ui::objectName, vars::circles[i].name.c_str(), sizeof(vars::circles[i].name));
							ui::itemInspecting = i;
							break;
						}
						if (ui::object_creation_menu) 
							ui::object_creation_menu = false;
				}
				
				//rmb
				else if (event.mouseButton.button == sf::Mouse::Right) {
					ui::object_creation_menu = true;
					ui::cursorpos = sf::Mouse::getPosition(window);
				}
			}
		}
		if (event.type == sf::Event::Closed) { log_ok("Closing window"); window.close(); }
	}
}
