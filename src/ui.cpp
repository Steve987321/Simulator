#include "ui.h"
#include "vars.h"
#include "toad.h"
#include "imgui/imgui.h"

void ui::decorations()
{
	ImGuiStyle* style = &ImGui::GetStyle();

	style->FrameRounding = 3.f;
	style->GrabRounding = 2.f;

	//main colors 21 21 21, 36 36 36, 48 173 228
	ImU32 dark_gray = ImColor(21, 21, 21);
	ImU32 gray = ImColor(36, 36, 36);
	ImU32 light_gray = ImColor(46, 46, 46);
	ImU32 light_blue = ImColor(48, 173, 228);
	ImU32 lighter_blue = ImColor(147, 170, 180);
	ImU32 dark_blue = ImColor(147, 170, 180);
	ImU32 darker_white = ImColor(184, 184, 184);

	style->Colors[ImGuiCol_Button] = (ImColor)gray;
	style->Colors[ImGuiCol_ButtonHovered] = (ImColor)light_gray;
	style->Colors[ImGuiCol_ButtonActive] = ImColor(13, 13, 13);

	style->Colors[ImGuiCol_CheckMark] = (ImColor)light_blue;

	style->Colors[ImGuiCol_FrameBg] = (ImColor)gray;
	style->Colors[ImGuiCol_FrameBgHovered] = (ImColor)gray;
	style->Colors[ImGuiCol_FrameBgActive] = ImColor(13, 13, 13);

	style->Colors[ImGuiCol_TitleBg] = (ImColor)dark_gray;
	style->Colors[ImGuiCol_TitleBgActive] = (ImColor)light_blue;

	style->Colors[ImGuiCol_ScrollbarBg] = ImColor(15, 15, 15);
	style->Colors[ImGuiCol_ScrollbarGrab] = (ImColor)gray;
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = (ImColor)gray;
	style->Colors[ImGuiCol_ScrollbarGrabActive] = (ImColor)gray;

	style->Colors[ImGuiCol_SliderGrab] = (ImColor)gray;
	style->Colors[ImGuiCol_SliderGrabActive] = (ImColor)gray;

	style->Colors[ImGuiCol_Text] = (ImColor)darker_white;

	style->Colors[ImGuiCol_WindowBg] = (ImColor)dark_gray;

	style->Colors[ImGuiCol_HeaderHovered] = ImColor(55, 55, 55);
	style->Colors[ImGuiCol_HeaderActive] = (ImColor)light_gray;
	style->Colors[ImGuiCol_Header] = (ImColor)lighter_blue;
}

void ui::render_ui()
{

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

	for (int i = 0; i < vars::circles.size(); i++) {
		const bool is_selected = (itemInspecting == i);

		if (vars::circles[i].isActive) {
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
			if (ImGui::Selectable(vars::circles[i].name.c_str(), is_selected)) {
				strncpy(ui::objectName, vars::circles[i].name.c_str(), sizeof(vars::circles[i].name));
				itemInspecting = i;
			}
			ImGui::PopStyleColor();
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 157));
			if (ImGui::Selectable(vars::circles[i].name.c_str(), is_selected)) {
				strncpy(ui::objectName, vars::circles[i].name.c_str(), sizeof(vars::circles[i].name));
				itemInspecting = i;
			}
			ImGui::PopStyleColor();
		}
		
		if (is_selected)
			ImGui::SetItemDefaultFocus();			
	}

	ImGui::EndListBox();

	// old
	/*for (int i = 0; i < vars::circles.size(); i++) {
		if (ImGui::Button(vars::circles[i].name.c_str(), ImVec2(100, 20))) {
			strncpy(ui::objectName, vars::circles[i].name.c_str(), sizeof(circles[i].name));
			itemInspecting = i;
			break;
		}
	}
	*/

	if (ImGui::Button("Add")) toad::add_object(vars::circles);
	
	ImGui::End();

	//imgui
	ImGui::Begin("Object Options", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

	ImGui::SetNextItemWidth(ImGui::CalcTextSize(ui::objectName).x + 10.f);

	//TODO: make it so it acutally chagnes name
	ImGui::InputText("##ObjectName", ui::objectName, IM_ARRAYSIZE(objectName));
	ImGui::SameLine(); 
	ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 100.f);

	//delete object
	if (ImGui::Button("Delete")) toad::delete_object(vars::circles, itemInspecting);
	ImGui::SameLine();
	ImGui::Checkbox("##ActiveStatus", &vars::circles[itemInspecting].isActive);
	
	ImGui::ColorEdit3("Circle Color", vars::circles[itemInspecting].circleColor);
	ImGui::SliderFloat("Position X", &vars::circles[itemInspecting].posx, 0, toad::info::window_sizeX - 20);
	ImGui::SliderFloat("Position Y", &vars::circles[itemInspecting].posy, 0, toad::info::window_sizeY - 20);

	ImGui::BeginChild("Shape Options", ImVec2(ImGui::GetWindowWidth() - 20, 150), true);
	ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Shape Options").x / 2);
	ImGui::TextColored(ImColor(100, 100, 100), "Shape Options");
	ImGui::SliderFloat("Radius", &vars::circles[itemInspecting].radius, 0.5f, 50.f);
	ImGui::SliderInt("Segment Count", &vars::circles[itemInspecting].circleSegments, 3, 100);

	if (ImGui::Button("Apply")) {
		vars::circles[itemInspecting].circle.setPointCount(vars::circles[itemInspecting].circleSegments);
		vars::circles[itemInspecting].circle.setRadius(vars::circles[itemInspecting].radius);
	}

	ImGui::EndChild();

	ImGui::BeginChild("Physics Options", ImVec2(ImGui::GetWindowWidth() - 20, 150), true);
	ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - ImGui::CalcTextSize("Physics Options").x / 2);
	ImGui::TextColored(ImColor(100, 100, 100), "Physics Options");

	ImGui::SliderFloat("Object Mass", &vars::circles[itemInspecting].mass, 0.1f, 200.f);
	ImGui::Text("Velocity X = %f", vars::circles[itemInspecting].velx);
	ImGui::Text("Velocity Y = %f", vars::circles[itemInspecting].vely);
	if (ImGui::Button("Reset velocity")) {
		vars::circles[itemInspecting].velx = 0; vars::circles[itemInspecting].vely = 0;
	}
	//ImGui::SliderFloat("VelocityX", &vars::circles[itemInspecting].velx, 0.f, 1000.f);
	//ImGui::SliderFloat("VelocityY", &vars::circles[itemInspecting].vely, 0.f, 1000.f);

	ImGui::EndChild();
	ImGui::End();

	//global physics options
	ImGui::Begin("Global Settings", nullptr , ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	//ImGui::SliderFloat("Gravity Amount", &vars::g_gravityf, 0.1f, 10.f);
	ImGui::SliderFloat("simSpeed", &vars::g_simSpeed, 1000.f, 10000.f);

	ImGui::End();		
}
