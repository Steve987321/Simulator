//#pragma warning(disable:4996) CRT_SECURE_NOWARNIGNSfa;lkjl;kf...
#define DEBUG

#include "main.h"
#include "Circle.h"
#include "Physics.h"
#include "toadsim.h"
#include "vars.h"
#include "logger.h"
#include <Windows.h>

//global variables 
float vars::deltaTime = 0.f;
float vars::g_gravityf = 6.6742E-11;
float vars::g_simSpeed = 2000;

ImColor vars::colorTheme::dark_gray = ImColor(21, 21, 21);
ImColor vars::colorTheme::gray = ImColor(36, 36, 36);
ImColor vars::colorTheme::light_gray = ImColor(46, 46, 46);
ImColor vars::colorTheme::light_blue = ImColor(48, 173, 228);
ImColor vars::colorTheme::lighter_black = ImColor(26, 26, 26);

int main()
{
	//init
	g_log = std::make_unique<logger>();

	log_debug("Initializing");

	log_debug("Initializing objects");

	//add 2 circles to scene on start
	std::vector<Circle> circles;

	circles.push_back(Circle::Circle());
	circles.push_back(Circle::Circle());

	circles[0].name = "circle1";
	circles[0].setColor(255, 255, 255);
	circles[0].active = true;
	circles[0].circle.setPosition(200, 150);
	circles[0].velx = 0.00001f;

	circles[1].name = "circle2";
	circles[1].setColor(255, 255, 255);
	circles[1].active = true;
	circles[1].circle.setPosition(200, 200);
	circles[1].mass = 100;

	log_ok("Initialized objects");

	//vars for imgui
	char objectName[16] = "circle1";
	int itemInspecting = 0;
	bool object_creation_menu = false;
	sf::Vector2i cursorpos;
	//int fps


	//sfml init
	log_debug("Initializing window");

	sf::RenderWindow window(sf::VideoMode(toad::window_sizeX, toad::window_sizeY), toad::title);
	if (ImGui::SFML::Init(window)) log_ok("Initialized window");
	else log_errorf("Initialization failed %d", GetLastError());

	window.setFramerateLimit(60);
	sf::Clock deltaClock;
	sf::Time dt;

	while (window.isOpen()) {
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
						for (int i = 0; i < circles.size(); i++)
							if (circles[i].circle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
							{
								strncpy_s(objectName, circles[i].name.c_str(), sizeof(circles[i].name));
								itemInspecting = i;
								break;
							}
						if (object_creation_menu)
							object_creation_menu = false;
					}
				
					//rmb
					else if (event.mouseButton.button == sf::Mouse::Right) {
						object_creation_menu = true;
						cursorpos = sf::Mouse::getPosition(window);
					}
				}
			}

			if (event.type == sf::Event::Closed) { log_ok("Closing window"); window.close(); }
		}
		//apply pos data to real pos
		for (int i = 0; i < circles.size(); i++) {
			circles[i].posx = circles[i].circle.getPosition().x;
			circles[i].posy = circles[i].circle.getPosition().y;
		}

		//deltatime
		dt = deltaClock.restart();
		vars::deltaTime = dt.asSeconds();
		ImGui::SFML::Update(window, dt);

		//colors and styles
		ui::decorations();

		//TODO: make so when left click on dis window it dont go away
		if (object_creation_menu) {
			ImGui::SetNextWindowPos(ImVec2(cursorpos.x, cursorpos.y));
			ImGui::Begin("Create Object");

			//SELECTIONS

			ImGui::End();
		}
	
		//TODO: make settings for creating objects with specific options:
		//(checkbox("Spawn as active"))
		ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		
		ImGui::BeginListBox("##objectListBox", ImVec2(140, 120));

		for (int i = 0; i < circles.size(); i++) {
			const bool is_selected = (itemInspecting == i);

			if (circles[i].active) {
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
				if (ImGui::Selectable(circles[i].name.c_str(), is_selected)) {
					strncpy_s(objectName, circles[i].name.c_str(), sizeof(circles[i].name));
					itemInspecting = i;
				}
				ImGui::PopStyleColor();
			}
			else {
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 157));
				if (ImGui::Selectable(circles[i].name.c_str(), is_selected)) {
					strncpy_s(objectName, circles[i].name.c_str(), sizeof(circles[i].name));
					itemInspecting = i;
				}
				ImGui::PopStyleColor();
			}
			
			if (is_selected)
				ImGui::SetItemDefaultFocus();			
		}

		ImGui::EndListBox();

		// old
		/*for (int i = 0; i < circles.size(); i++) {
			if (ImGui::Button(circles[i].name.c_str(), ImVec2(100, 20))) {
				strncpy_s(objectName, circles[i].name.c_str(), sizeof(circles[i].name));
				itemInspecting = i;
				break;
			}
		}
		*/

		if (ImGui::Button("Add")) Object::add_object(circles);
		
		ImGui::End();

		//imgui
		ImGui::Begin("Object Options", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

		ImGui::SetNextItemWidth(ImGui::CalcTextSize(objectName).x + 10.f);

		//TODO: make it so it acutally chagnes name
		ImGui::InputText("##ObjectName", objectName, IM_ARRAYSIZE(objectName));
		ImGui::SameLine(); 
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 100.f);

		//delete object
		if (ImGui::Button("Delete")) Object::delete_object(circles, itemInspecting);
		ImGui::SameLine();
		ImGui::Checkbox("##ActiveStatus", &circles[itemInspecting].active);
		
		ImGui::ColorEdit3("Circle Color", circles[itemInspecting].circleColor);
		ImGui::SliderFloat("Position X", &circles[itemInspecting].posx, 0, toad::window_sizeX - 20);
		ImGui::SliderFloat("Position Y", &circles[itemInspecting].posy, 0, toad::window_sizeY - 20);

		ImGui::BeginChild("Shape Options", ImVec2(ImGui::GetWindowWidth() - 20, 150), true);
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Shape Options").x / 2);
		ImGui::TextColored(ImColor(100, 100, 100), "Shape Options");
		ImGui::SliderFloat("Radius", &circles[itemInspecting].radius, 0.5f, 50.f);
		ImGui::SliderInt("Segment Count", &circles[itemInspecting].circleSegments, 3, 100);

		if (ImGui::Button("Apply")) {
			circles[itemInspecting].circle.setPointCount(circles[itemInspecting].circleSegments);
			circles[itemInspecting].circle.setRadius(circles[itemInspecting].radius);
		}

		ImGui::EndChild();

		ImGui::BeginChild("Physics Options", ImVec2(ImGui::GetWindowWidth() - 20, 150), true);
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Physics Options").x / 2);
		ImGui::TextColored(ImColor(100, 100, 100), "Physics Options");

		ImGui::SliderFloat("Object Mass", &circles[itemInspecting].mass, 0.1f, 200.f);
		ImGui::Text("Velocity X = %f", circles[itemInspecting].velx);
		ImGui::Text("Velocity Y = %f", circles[itemInspecting].vely);
		if (ImGui::Button("Reset velocity")) {
			circles[itemInspecting].velx = 0; circles[itemInspecting].vely = 0;
		}
		//ImGui::SliderFloat("VelocityX", &circles[itemInspecting].velx, 0.f, 1000.f);
		//ImGui::SliderFloat("VelocityY", &circles[itemInspecting].vely, 0.f, 1000.f);

		ImGui::EndChild();
		ImGui::End();

		//global physics options
		ImGui::Begin("Global Settings", nullptr , ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		//ImGui::SliderFloat("Gravity Amount", &vars::g_gravityf, 0.1f, 10.f);
		ImGui::SliderFloat("simSpeed", &vars::g_simSpeed, 1000.f, 10000.f);

		ImGui::End();		

		//options to update live
		circles[itemInspecting].circle.setPosition(sf::Vector2f(circles[itemInspecting].posx, circles[itemInspecting].posy));
		circles[itemInspecting].circle.setFillColor(sf::Color(circles[itemInspecting].circleColor[itemInspecting] * 255, circles[itemInspecting].circleColor[1] * 255, circles[itemInspecting].circleColor[2] * 255));

		//update pos 
		for (Circle& ci : circles) {
			if (ci.active) {
				ci.update_position(ci, circles, vars::g_simSpeed * 1000 * vars::deltaTime);
			}
		}
		
		window.clear(sf::Color::Black);

		//--------------------draw here------------------------//

		//draw shapes color problem?? 255 255 255
		for (Circle ci : circles)
			if (ci.active) 
				window.draw(ci.circle);

		//draw ui
		ImGui::SFML::Render(window);

		//--------------------draw here-------------------------//

		window.display();
	}
	ImGui::SFML::Shutdown();
	return 0;
}