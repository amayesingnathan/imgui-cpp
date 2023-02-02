module;

#include <imgui_internal.h>

module imcpp.utils;

namespace imcpp {

	bool Utils::IsMouseDown(ImGuiMouseButton button)
	{
		return ImGui::IsMouseDown(button);
	}

	bool Utils::IsMouseReleased(ImGuiMouseButton button)
	{
		return ImGui::IsMouseReleased(button);
	}

	ImVec2 Utils::CursorPos()
	{
		return ImGui::GetCursorPos();
	}

	void Utils::SetCursorPos(float x, float y)
	{
		ImGui::SetCursorPos(ImVec2(x, y));
	}

	void Utils::SetCursorPosX(float pos)
	{
		ImGui::SetCursorPosX(pos);
	}

	void Utils::SetCursorPosY(float pos)
	{
		ImGui::SetCursorPosY(pos);
	}

	void Utils::SetButtonTransparent()
	{
		auto& colours = ImGui::GetStyle().Colors;
		const auto& buttonHovered = colours[ImGuiCol_ButtonHovered];
		const auto& buttonActive = colours[ImGuiCol_ButtonActive];

		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	}

	void Utils::ResetButtonTransparency()
	{
		ImGui::PopStyleColor(3);
	}

	ImVec2 Utils::AvailableRegion()
	{
		return ImGui::GetContentRegionAvail();
	}

	ImVec2 Utils::AvailableRegionMax()
	{
		return ImGui::GetWindowContentRegionMax();
	}

	float Utils::FontSize()
	{
		return GImGui->Font->FontSize;
	}

	ImVec2 Utils::FramePadding()
	{
		return GImGui->Style.FramePadding;
	}

	float Utils::FrameHeightWithSpacing()
	{
		return ImGui::GetFrameHeightWithSpacing();
	}

	float Utils::LineHeight()
	{
		return GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
	}

	float Utils::WindowWidth()
	{
		return ImGui::GetWindowWidth();
	}

	float Utils::WindowHeight()
	{
		return ImGui::GetWindowHeight();
	}

	void Utils::PushItemWidth(float width)
	{
		ImGui::PushItemWidth(width);
	}

	void Utils::PopItemWidth()
	{
		ImGui::PopItemWidth();
	}

	void Utils::PushID(std::string_view strID)
	{
		ImGui::PushID(strID.data());
	}

	void Utils::PopID()
	{
		ImGui::PopID();
	}

	void Utils::PushStyle(ImGuiStyleVar flags, float var)
	{
		ImGui::PushStyleVar(flags, var);
	}

	void Utils::PushStyle(ImGuiStyleVar flags, const ImVec2& var)
	{
		ImGui::PushStyleVar(flags, var);
	}

	void Utils::PopStyle(int count)
	{
		ImGui::PopStyleVar(count);
	}

	void Utils::PushStyleColour(ImGuiCol flags, const ImVec4& var)
	{
		ImGui::PushStyleColor(flags, var);
	}

	void Utils::PopStyleColour()
	{
		ImGui::PopStyleColor();
	}
}