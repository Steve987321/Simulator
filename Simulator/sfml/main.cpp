//#pragma warning(disable:4996) CRT_SECURE_NOWARNIGNSfa;lkjl;kf...

#include "main.h"
#include "Circle.h"
#include "Physics.h"
#include "toadsim.h"

#include <Windows.h>

int main()
{
	std::vector<Circle> circles;
	
	//5 circle objects
	circles.push_back(Circle::Circle());

	circles[0].name = "circle1";
	circles[0].setColor(255, 255, 255);
	circles[0].active = true;

	//vars for imgui
	char objectName[16] = "";
	int itemInspecting = 0;

	//sfml init
	sf::RenderWindow window(sf::VideoMode(toad::info::window_sizeX, toad::info::window_sizeY), toad::info::title);
	ImGui::SFML::Init(window);
	
	sf::Clock deltaClock;

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
		sf::Time dt = deltaClock.restart();
		
		ImGui::SFML::Update(window, dt);

		//all the objects 
		ImGui::Begin("Scene");

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
		ImGui::Begin("Object Options", nullptr);//ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

		ImGui::SetNextItemWidth(ImGui::CalcTextSize(objectName).x + 10.f);
		ImGui::InputText("##ObjectName", objectName, IM_ARRAYSIZE(objectName));
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 100.f);

		//delete object
		if (ImGui::Button("Delete")) gameObject::delete_object(circles, itemInspecting);
		ImGui::SameLine();
		ImGui::Checkbox("##ActiveStatus", &circles[itemInspecting].active);
		
		ImGui::ColorEdit3("Circle Color", circles[itemInspecting].circleColor);
		ImGui::SliderFloat("Position X", &circles[itemInspecting].posx, 0, toad::info::window_sizeX - 20);
		ImGui::SliderFloat("Position Y", &circles[itemInspecting].posy, 0, toad::info::window_sizeY - 20);

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

		ImGui::SliderFloat("Object Mass", &circles[itemInspecting].mass, 0.f, 20.f);

		//ImGui::Checkbox("Emit Gravity", &toad::physics::gravity);

		ImGui::EndChild();

		ImGui::End();

		ImGui::Begin("Global Settings");

		ImGui::Checkbox("Gravity", &toad::physics::gravity);
		ImGui::SliderFloat("Gravity Amount", &toad::physics::gravityf, 0.1f, 10.f);

		ImGui::End();

		//update gravity
		if (toad::physics::gravity) {
			for (int i = 0; i < circles.size(); i++) {
				if (circles[i].active) {
					if (circles[i].circle.getPosition().y < toad::info::window_sizeY - circles[i].circle.getRadius()) {
						float distance = circles[i].circle.getPosition().y - toad::info::window_sizeY - circles[i].circle.getRadius();
						float pos = physics::calc_gravity_velocity(circles[i].mass, distance, toad::physics::gravityf);
						circles[i].posy -= pos * dt.asSeconds() * 1000;
						circles[i].circle.setPosition(circles[i].posx, circles[i].posy);
						//y += toad::physics::gravityf
					}
				}
			}
		}

		//options to update live
		circles[itemInspecting].circle.setPosition(sf::Vector2f(circles[itemInspecting].posx, circles[itemInspecting].posy));
		circles[itemInspecting].circle.setFillColor(sf::Color(circles[itemInspecting].circleColor[itemInspecting] * 255, circles[itemInspecting].circleColor[1] * 255, circles[itemInspecting].circleColor[2] * 255));

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