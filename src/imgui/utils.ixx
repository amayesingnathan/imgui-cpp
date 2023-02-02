export module imcpp.utils;

export import <imgui.h>;
export import imcpp.std;

namespace imcpp {

	export class Utils 
	{
	public:
		static bool IsMouseDown(ImGuiMouseButton button);
		static bool IsMouseReleased(ImGuiMouseButton button);

		static ImVec2 CursorPos();
		static void SetCursorPos(float x, float y);
		static void SetCursorPosX(float pos);
		static void SetCursorPosY(float pos);

		static void SetButtonTransparent();
		static void ResetButtonTransparency();

		static ImVec2 AvailableRegion();
		static ImVec2 AvailableRegionMax();

		static float FontSize();
		static ImVec2 FramePadding();
		static float FrameHeightWithSpacing();

		static float LineHeight();

		static float WindowWidth();
		static float WindowHeight();

		static void PushItemWidth(float width);
		static void PopItemWidth();

		static void PushID(std::string_view strID);
		static void PopID();

		static void PushStyle(ImGuiStyleVar flags, float var);
		static void PushStyle(ImGuiStyleVar flags, const ImVec2& var);
		static void PopStyle(int count = 1);

		static void PushStyleColour(ImGuiCol flags, const ImVec4& var);
		static void PopStyleColour();
	};
}