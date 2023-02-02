module;

#include "GLFW/glfw3.h"

module imcpp.control;

namespace imcpp {

    ImScopedFrame::ImScopedFrame(const WindowSizeCallback& sizeCallback)
        : mWindowSizeCallback(sizeCallback)
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
            GLFWwindow* backupContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupContext);
        }
    }

	ImHandler::ImHandler(WindowGetCallback&& winCallback, WindowSizeCallback&& sizeCallback)
		: mWindowGetCallback(std::move(winCallback)), mWindowSizeCallback(std::move(sizeCallback))
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