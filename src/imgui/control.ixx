export module imcpp.control;

import "imgui.h";
import "backends/imgui_impl_glfw.h";
import "backends/imgui_impl_opengl3.h";

import imcpp.def;

export namespace imcpp {

	using WindowGetCallback  = Func<void*>;
	using WindowSizeCallback = Func<ImVec2>;

	class ImScopedFrame
	{
	public:
		ImScopedFrame() = delete;
		explicit ImScopedFrame(const WindowSizeCallback& sizeCallback);
		~ImScopedFrame();

		ImScopedFrame(const ImScopedFrame&) = delete;
		ImScopedFrame& operator=(const ImScopedFrame&) = delete;

		ImScopedFrame(ImScopedFrame&&) noexcept = delete;
		ImScopedFrame& operator=(ImScopedFrame&&) noexcept = delete;

	private:
		const WindowSizeCallback& mWindowSizeCallback;
	};

	class ImHandler
	{
	public:
		ImHandler() = delete;
		ImHandler(WindowGetCallback&& winCallback, WindowSizeCallback&& sizeCallback);
		~ImHandler();

		ImHandler(const ImHandler&) = delete;
		ImHandler& operator=(const ImHandler&) = delete;

		ImHandler(ImHandler&&) = delete;
		ImHandler& operator=(ImHandler&&) = delete;

		// On the stack as every frame.
		[[nodiscard]] ImScopedFrame newFrame() const { return ImScopedFrame(mWindowSizeCallback); }

	private:
		void SetDarkThemeColours();

	private:
		WindowGetCallback mWindowGetCallback;
		WindowSizeCallback mWindowSizeCallback;
	};
}