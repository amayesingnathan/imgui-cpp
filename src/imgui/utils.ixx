export module imcpp.utils;

export import <imgui.h>;
export import imcpp.std;

namespace imcpp {

	template<typename T>
	concept ImVecType = std::same_as<T, ImVec2> || std::same_as<T, ImVec3> || std::same_as<T, ImVec4>;

	template<typename T, typename V>
	concept VecSized = requires { sizeof(T) == sizeof(V); };

	export class Utils 
	{
	public:
		template<ImVecType Vec, typename T> requires VecSized<Vec, T>
		static const Vec& ToImVec(const T& var) { return (Vec*)&var; }

		template<ImVecType Vec, typename T> requires VecSized<Vec, T>
		static const T& FromImVec(const Vec& var) { return (T*)&var; }

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