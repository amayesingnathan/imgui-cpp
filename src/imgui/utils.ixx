export module imcpp.utils;

export import <imgui.h>;
export import imcpp.std;
export import imcpp.containers.dummy;

export namespace imcpp {

	template<typename T>
	concept ImVecType = std::same_as<T, ImVec2> || std::same_as<T, ImVec3> || std::same_as<T, ImVec4>;

	template<typename Vec, typename T>
	concept VecSized = std::is_standard_layout_v<T> && std::is_trivially_copyable_v<T> && requires { sizeof(Vec) == sizeof(T); };

	class Utils 
	{
	public:
		template<ImVecType Vec, typename T> requires VecSized<Vec, T>
		static Vec& ToImVec(T& var) { return *reinterpret_cast<Vec*>(&var); }
		template<ImVecType Vec, typename T> requires VecSized<Vec, T>
		static const Vec& ToImVec(const T& var) { return *reinterpret_cast<const Vec*>(&var); }

		template<typename T, ImVecType Vec> requires VecSized<Vec, T>
		static T& FromImVec(Vec& var) { return *reinterpret_cast<T*>(&var); }
		template<typename T, ImVecType Vec> requires VecSized<Vec, T>
		static const T& FromImVec(const Vec& var) { return *reinterpret_cast<const T*>(&var); }

		static bool IsKeyPressed(int key);
		static bool IsMouseDown(ImGuiMouseButton button);
		static bool IsMouseReleased(ImGuiMouseButton button);

		template<typename T = ImCppVec2> requires VecSized<ImVec2, T>
		static T MousePos() { return FromImVec<T>(MousePosInternal()); }

		template<typename T = ImCppVec2> requires VecSized<ImVec2, T>
		static T CursorPos() { return FromImVec<T>(CursorPosInternal()); }
		static void SetCursorPos(float x, float y);
		static void SetCursorPosX(float pos);
		static void SetCursorPosY(float pos);

		template<typename T = ImCppVec2> requires VecSized<ImVec2, T>
		static T WindowPos() { return FromImVec<T>(WindowPosInternal()); }

		template<typename T = ImCppVec2> requires VecSized<ImVec2, T>
		static void SetNextWindowSize(const T& size, ImGuiCond cond = ImGuiCond_FirstUseEver) { SetNextWindowSizeInternal(ToImVec<ImVec2>(size), cond); }
		template<typename T = ImCppVec2> requires VecSized<ImVec2, T>
		static void SetNextWindowPos(const T& size, const T& pivot = T(0, 0), ImGuiCond cond = ImGuiCond_FirstUseEver) { SetNextWindowPosInternal(ToImVec<ImVec2>(size), ToImVec<ImVec2>(pivot), cond); }

		static void SetButtonTransparent();
		static void ResetButtonTransparency();

		template<typename T = ImCppVec2> requires VecSized<ImVec2, T>
		static T GetMainWindowCentre() { return FromImVec<T>(GetMainWindowCentreInternal()); }

		static void SetWindowMoveFromTitleBar(bool titleBarOnly = true);

		template<typename T = ImCppVec2> requires VecSized<ImVec2, T>
		static T AvailableRegion() { return FromImVec<T>(AvailableRegionInternal()); }
		template<typename T = ImCppVec2> requires VecSized<ImVec2, T>
		static T AvailableRegionMax() { return FromImVec<T>(AvailableRegionMaxInternal()); }
		template<typename T = ImCppVec2> requires VecSized<ImVec2, T>
		static T AvailableRegionMin() { return FromImVec<T>(AvailableRegionMinInternal()); }

		static float FontSize();
		template<typename T = ImCppVec2> requires VecSized<ImVec2, T>
		static T FramePadding() { return FromImVec<T>(FramePaddingInternal()); }
		static float FrameHeightWithSpacing();

		static float LineHeight();

		static float WindowWidth();
		static float WindowHeight();

		static bool WindowFocused();
		static bool WindowHovered();

		static void PushItemWidth(float width);
		static void PopItemWidth();

		static void PushID(std::string_view strID);
		static void PopID();

		static void PushStyle(ImGuiStyleVar flags, float var);
		static void PushStyle(ImGuiStyleVar flags, const ImVec2& var);
		static void PopStyle(int count = 1);

		static void PushStyleColour(ImGuiCol flags, const ImVec4& var);
		static void PopStyleColour();

	private:
		static ImVec2 CursorPosInternal();
		static ImVec2 MousePosInternal();
		static ImVec2 WindowPosInternal();
		static ImVec2 GetMainWindowCentreInternal();

		static void SetNextWindowSizeInternal(const ImVec2& size, ImGuiCond cond = ImGuiCond_FirstUseEver);
		static void SetNextWindowPosInternal(const ImVec2& size, const ImVec2& pivot = ImVec2(0, 0), ImGuiCond cond = ImGuiCond_FirstUseEver);

		static ImVec2 AvailableRegionInternal();
		static ImVec2 AvailableRegionMinInternal();
		static ImVec2 AvailableRegionMaxInternal();

		static ImVec2 FramePaddingInternal();
	};
}