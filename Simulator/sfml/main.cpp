//#pragma warning(disable:4996) CRT_SECURE_NOWARNIGNSfa;lkjl;kf...

#include "main.h"
#include "Circle.h"

int main()
{
	float groundlevel = 780.f;

	Circle c1("Circle1");

	sf::RenderWindow window(sf::VideoMode(tsim::info::window_sizeX, tsim::info::window_sizeY), tsim::info::title);
	
	ImGui::SFML::Init(window);

	sf::CircleShape circle(20.f);
	circle.setFillColor(sf::Color::Red);
	circle.setOutlineColor(sf::Color(2, 2, 2));
	circle.setScale(sf::Vector2f(0.5, 0.5));
	circle.setPosition(sf::Vector2f(10, 10));

	c1.circleSegments = circle.getPointCount();
	
	sf::Clock deltaClock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			//events

			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					//test = !test;
					if (circle.getLocalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
						c1.inspecting = true;
					}
					else {
						c1.inspecting = false;
					}
					circle.getGlobalBounds();
				}
			}

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		//imgui
		ImGui::Begin("Object Options", nullptr);//ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

		c1.posx = circle.getPosition().x;
		c1.posy = circle.getPosition().y;

		ImGui::ColorEdit3("Circle Color", c1.circleColor);
		ImGui::SliderFloat("Position X", &c1.posx, 0, tsim::info::window_sizeX - 20);
		ImGui::SliderFloat("Position Y", &c1.posy, 0, tsim::info::window_sizeY- 20);

		ImGui::BeginChild("Shape Options", ImVec2(ImGui::GetWindowWidth() - 20, 150), true);
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Shape Options").x / 2);
		ImGui::TextColored(ImColor(100, 100, 100),"Shape Options");
		ImGui::SliderFloat("Circle Scale X", &c1.circleScaleX, 0.1f, 10.f);
		ImGui::SliderFloat("Circle Scale Y", &c1.circleScaleY, 0.1f, 10.f);
		ImGui::SliderInt("Segment Count", &c1.circleSegments, 3, 100);

		if (ImGui::Button("Apply")) {
			circle.setPointCount(c1.circleSegments);
			circle.setScale(c1.circleScaleX, c1.circleScaleY);
		}

		ImGui::EndChild();

		ImGui::BeginChild("Physics Options", ImVec2(ImGui::GetWindowWidth() - 20, 150), true);
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Physics Options").x / 2);
		ImGui::TextColored(ImColor(100, 100, 100), "Physics Options");

		ImGui::SliderFloat("Object Mass", &c1.mass, 0.f, 20.f);

		//ImGui::Checkbox("Emit Gravity", &tsim::physics::gravity);

		ImGui::EndChild();

		ImGui::End();
		

		ImGui::Begin("Global Settings");

		ImGui::Checkbox("Gravity", &tsim::physics::gravity);
		ImGui::Text("Formula: velocity = Gravity Amount(massobj1 * massobj2) / distance");
		ImGui::SliderFloat("Gravity Amount", &tsim::physics::gravityf, 0.1f, 10.f);

		ImGui::End();
		//background circleColoror
		window.clear(sf::Color::Black);

		if (tsim::physics::gravity) {
			if (circle.getPosition().y < groundlevel) {
				float distance = circle.getPosition().y - groundlevel;
				float vel = tsim::physics::gravityf * (c1.mass / distance);
				c1.posy -= vel;
				//y += tsim::physics::gravityf
			}
		}

		circle.setPosition(sf::Vector2f(c1.posx, c1.posy));
		circle.setFillColor(sf::Color(c1.circleColor[0] * 255, c1.circleColor[1] * 255, c1.circleColor[2] * 255));

		///////draw here//////
		
		window.draw(circle);
		ImGui::SFML::Render(window);

		///////draw here//////


		window.display();
	}
	ImGui::SFML::Shutdown();
	return 0;
}