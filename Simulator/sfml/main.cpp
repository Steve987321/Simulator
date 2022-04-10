//#pragma warning(disable:4996) CRT_SECURE_NOWARNIGNSfa;lkjl;kf...

#include "main.h"
#include "Circle.h"
#include "Physics.h"
#include "toadsim.h"
#include "vars.h"
#include <Windows.h>

bool vars::gravity = false;
float vars::gravityf = 6.6742E-11;
float vars::groundmass = 5.f;
float vars::deltaTime = 0.f;
float vars::simSpeed = 2000; // day

int main()
{
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
	

	//vars for imgui
	char objectName[16] = "circle1";
	int itemInspecting = 0;

	//sfml init
	sf::RenderWindow window(sf::VideoMode(toad::window_sizeX, toad::window_sizeY), toad::title);
	ImGui::SFML::Init(window);
	
	sf::Clock deltaClock;
	sf::Time dt;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			//events

			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::MouseButtonPressed) {

				if (event.mouseButton.button == sf::Mouse::Left)
					if (sf::Mouse::getPosition(window).x < 600)
						for (int i = 0; i < circles.size(); i++)
							if (circles[i].circle.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
							{
								strncpy_s(objectName, circles[i].name.c_str(), sizeof(circles[i].name));
								itemInspecting = i;
								break;
							}
			}
			if (event.type == sf::Event::Closed) {
				window.close();
			}
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

		//all the objects 

		//TODO: make settings for creating objects with specific options:
		//(checkbox("Spawn as active"))
		ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

		for (int i = 0; i < circles.size(); i++) {
			if (ImGui::Button(circles[i].name.c_str(), ImVec2(100, 20))) {
				strncpy_s(objectName, circles[i].name.c_str(), sizeof(circles[i].name));
				itemInspecting = i;
				break;
			}
		}

		if (ImGui::Button("Add")) gameObject::add_object(circles);
		
		ImGui::End();

		//imgui
		ImGui::Begin("Object Options", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

		ImGui::SetNextItemWidth(ImGui::CalcTextSize(objectName).x + 10.f);

		//TODO: make it so it acutally chagnes name
		ImGui::InputText("##ObjectName", objectName, IM_ARRAYSIZE(objectName));
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 100.f);

		//delete object
		if (ImGui::Button("Delete")) gameObject::delete_object(circles, itemInspecting);
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
		//ImGui::SliderFloat("VelocityX", &circles[itemInspecting].velx, 0.f, 1000.f);
		//ImGui::SliderFloat("VelocityY", &circles[itemInspecting].vely, 0.f, 1000.f);

		ImGui::EndChild();
		ImGui::End();

		//global physics options
		ImGui::Begin("Global Settings", nullptr , ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

		ImGui::Checkbox("Gravity", &vars::gravity);
		ImGui::SliderFloat("Gravity Amount", &vars::gravityf, 0.1f, 10.f);
		ImGui::SliderFloat("TimeStep", &vars::simSpeed, 1000.f, 5000.f);

		ImGui::End();		

		//update ground gravity temp
		/*
		if (vars::physics::gravity) {
			for (int i = 0; i < circles.size(); i++) {
				if (circles[i].active) {
					if (circles[i].circle.getPosition().y < toad::window_sizeY - circles[i].circle.getRadius()) {
						float distance = circles[i].circle.getPosition().y - toad::window_sizeY - circles[i].circle.getRadius();
						float pos = physics::calc_gravity_velocity(circles[i].mass, distance, vars::physics::gravityf);
						circles[i].posy -= pos * dt.asSeconds() * 1000;
						circles[i].circle.setPosition(circles[i].posx, circles[i].posy);
						//y += vars::physics::gravityf
					}
				}
			}
		}*/

		//options to update live
		circles[itemInspecting].circle.setPosition(sf::Vector2f(circles[itemInspecting].posx, circles[itemInspecting].posy));
		circles[itemInspecting].circle.setFillColor(sf::Color(circles[itemInspecting].circleColor[itemInspecting] * 255, circles[itemInspecting].circleColor[1] * 255, circles[itemInspecting].circleColor[2] * 255));

		//update pos 
		for (Circle& ci : circles) {
			if (ci.active) {
				ci.update_position(ci, circles, vars::simSpeed);
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