
#include <wtypes.h>
#include <Core.hpp>
#include <ImGui/imgui.h>
using namespace ImGui;

ImFont* font_main;
ImFont* font_menu;


ImFont* icons = nullptr;
ImFont* info_big = nullptr;
ImFont* two = nullptr;
ImFont* three = nullptr;
ImFont* tabsf = nullptr;
ImFont* ee = nullptr;
ImVec2 pos;

void apply_fonts() {
	ImGui::CreateContext();

	font_main = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 18);
	font_menu = ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 12);
}
void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("[?]");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
VOID ImGUI_Style()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;
	ImGui::StyleColorsDark();

	style->FrameBorderSize = 1.0f;
	style->FramePadding = ImVec2(4.0f, 2.0f);
	style->ItemSpacing = ImVec2(8.0f, 2.0f);
	style->WindowBorderSize = 1.0f;
	style->WindowRounding = 1.0f;
	style->ChildRounding = 1.0f;
	style->AntiAliasedFill = true;
	style->AntiAliasedLines = true;
	style->WindowBorderSize = 0.0f;

	// Setup style
	//ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.18f, 0.18f, 0.18f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.44f, 0.44f, 0.44f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.46f, 0.47f, 0.48f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.70f, 0.70f, 0.70f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.70f, 0.70f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.48f, 0.50f, 0.52f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.72f, 0.72f, 0.72f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.73f, 0.60f, 0.15f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	//colors[ImGuiCol_TabButton] = ImVec4(0.08f, 0.08f, 0.08f, 1.f);
	//colors[ImGuiCol_TabButtonHovered] = ImVec4(0.08f, 0.08f, 0.08f, 1.f);
	//colors[ImGuiCol_TabButtonActive] = ImVec4(0.08f, 0.08f, 0.08f, 1.f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.87f, 0.87f, 0.87f, 0.35f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
}


#include <mutex>
#include <tchar.h>
#include "xorstr.hpp"
#include "sdk.h"
#include "icons.h"


void DrawMenu()
{
	ImGUI_Style();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;
	colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15, 255);
	if (ImGui::Begin("NiggaWare.cc"), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(300, screen_size.y), ImGuiCond_Always);

		ImGui::End();
	}

	ImGUI_Style();
	static int page = 0;
	if (ImGui::Begin(("NiggaWare.cc"), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::SetCursorPos({ 15,10 - ImGui::CalcTextSize(("NiggaWare.cc")).y / 2 });
		ImGui::Text(("NiggaWare.cc"));
		ImGui::SetCursorPos({ 150,1 });
		ImGui::SetWindowPos(ImVec2(500, 200), ImGuiCond_Once);
		ImGui::SetWindowSize(ImVec2(375, 225), ImGuiCond_Once);
		static int tabb = 1;
		ImGui::SameLine();
		if (ImGui::Button(("Visual")))
		{
			tabb = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button(("MISC")))
		{
			tabb = 1;
		}
		ImGui::Separator();
		switch (tabb) {
		case 0:
			ImGui::Checkbox(("ESP"), &VARS::Drawing);
			ImGui::Checkbox(("Include NPC"), &VARS::drawnpc);
			ImGui::Checkbox(("healthbar"), &VARS::healthbar);
			ImGui::Checkbox(("Silent"), &VARS::Silent);
			ImGui::Checkbox(("FOV Circle"), &VARS::fovcircle);
			if (VARS::fovcircle) {
				ImGui::SliderFloat(("AIMFOV"), &VARS::f_circlefov, 20, 360, ("FOV: %.0f"));
				}
			ImGui::ColorEdit3((("Fov Circle Color")), VARS::fov_circle_color);
			break;
		case 1:
			ImGui::Checkbox(("Noclip"), &VARS::Noclip);
			ImGui::Checkbox(("Instant Eoka"), &VARS::instantoka);
			ImGui::Checkbox(("Fake admin"), &VARS::fakeadmin);
			ImGui::Checkbox(("No Recoil"), &VARS::NoRecoil);
			//ImGui::SliderFloat(xorstr("Thick bullet"), &VARS::desiredfov, 20, 180, xorstr("FOV: %.0f"));
			//uintptr_t Graphics = mem::read<uintptr_t>(SDK::GameAssembly + SDK::Graphics);
			//uintptr_t GraphicsInstance = mem::read<uintptr_t>(Graphics + 0xB8);
			//mem::write<float>(GraphicsInstance + 0x18, VARS::desiredfov);
			//break;
		}
		ImGui::End();
	}
}