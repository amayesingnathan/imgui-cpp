module imcpp.control;

namespace imcpp {

    ImScopedFrame::ImScopedFrame(const WindowGetCallback& winCallback, const WindowSizeCallback& sizeCallback, const ContextGetCallback& ctxGetCallback, const ContextSetCallback& ctxSetCallback)
        : mWindowGetCallback(winCallback), mWindowSizeCallback(sizeCallback),
          mContextGetCallback(ctxGetCallback), mContextSetCallback(ctxSetCallback)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    ImScopedFrame::~ImScopedFrame()
    {
        ImGuiIO& io = ImGui::GetIO();

        io.DisplaySize = mWindowSizeCallback();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            void* backupContext = mContextGetCallback();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            mContextSetCallback(backupContext);
        }
    }

	ImHandler::ImHandler(WindowGetCallback&& winCallback, WindowSizeCallback&& sizeCallback, ContextGetCallback&& ctxGetCallback, ContextSetCallback&& ctxSetCallback)
		: mWindowGetCallback(std::move(winCallback)), mWindowSizeCallback(std::move(sizeCallback)), 
          mContextGetCallback(std::move(ctxGetCallback)), mContextSetCallback(std::move(ctxSetCallback))
	{
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        { 
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)mWindowGetCallback(), true);
        ImGui_ImplOpenGL3_Init("#version 410");
	}

    ImHandler::~ImHandler()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}