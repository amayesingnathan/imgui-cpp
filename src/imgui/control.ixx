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
		explicit ImScopedFrame(const WindowSizeCallback& sizeCallback);
		~ImScopedFrame();

		ImScopedFrame(const ImScopedFrame&) = delete;
		ImScopedFrame& operator=(const ImScopedFrame&) = delete;

		ImScopedFrame(ImScopedFrame&&) = default;
		ImScopedFrame& operator=(ImScopedFrame&&) = default;

	private:
		const WindowSizeCallback& mWindowSizeCallback;
	};

	class ImHandler
	{
	public:
		ImHandler(WindowGetCallback&& winCallback, WindowSizeCallback&& sizeCallback);
		~ImHandler();

		[[nodiscard]] ImScopedFrame newFrame() const { return ImScopedFrame(mWindowSizeCallback); }

	private:
		WindowGetCallback mWindowGetCallback;
		WindowSizeCallback mWindowSizeCallback;
	};
}