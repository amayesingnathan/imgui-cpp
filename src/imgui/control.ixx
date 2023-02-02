export module imcpp.control;

import "imgui.h";
import "backends/imgui_impl_glfw.h";
import "backends/imgui_impl_opengl3.h";

import imcpp.def;

struct GLFWwindow;

export namespace imcpp {

	using WindowGetCallback  = Func<void*>;
	using WindowSizeCallback = Func<ImVec2>;

	using ContextGetCallback = Func<void*>;
	using ContextSetCallback = Action<void*>;

	class ImScopedFrame
	{
	public:
		explicit ImScopedFrame(const WindowGetCallback& winCallback, const WindowSizeCallback& sizeCallback, const ContextGetCallback& ctxGetCallback, const ContextSetCallback& ctxSetCallback);
		~ImScopedFrame();

		ImScopedFrame(const ImScopedFrame&) = delete;
		ImScopedFrame& operator=(const ImScopedFrame&) = delete;

		ImScopedFrame(ImScopedFrame&&) = default;
		ImScopedFrame& operator=(ImScopedFrame&&) = default;

	private:
		const WindowGetCallback& mWindowGetCallback;
		const WindowSizeCallback& mWindowSizeCallback;
		const ContextGetCallback& mContextGetCallback;
		const ContextSetCallback& mContextSetCallback;
	};

	class ImHandler
	{
	public:
		ImHandler(WindowGetCallback&& winCallback, WindowSizeCallback&& sizeCallback, ContextGetCallback&& ctxGetCallback, ContextSetCallback&& ctxSetCallback);
		~ImHandler();

		[[nodiscard]] ImScopedFrame newFrame() const { return ImScopedFrame(mWindowGetCallback, mWindowSizeCallback, mContextGetCallback, mContextSetCallback); }

	private:
		WindowGetCallback mWindowGetCallback;
		WindowSizeCallback mWindowSizeCallback;
		ContextGetCallback mContextGetCallback;
		ContextSetCallback mContextSetCallback;
	};
}