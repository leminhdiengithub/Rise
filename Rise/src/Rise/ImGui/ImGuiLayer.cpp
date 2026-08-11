#include "rscph.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"	
#include "Platform/OpenGL/imgui_impl_glfw.h"	

#include "Rise/Application.h"

//TEMPORATY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Rise
{
	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer") {
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		SetDarkThemeColors();

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, false);

		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseButtonPressedEvent>(RS_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(RS_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(RS_BIND_EVENT_FN(ImGuiLayer::OnMouseMoveEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(RS_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(RS_BIND_EVENT_FN(ImGuiLayer::OnKeyPressdEvent));
		//dispatcher.Dispatch<OnKeyTypeEvent>(RS_BIND_EVENT_FN(ImGuiLayer::OnKeyTypeEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(RS_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(RS_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));

	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}


	bool ImGuiLayer::OnMouseMoveEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetX(), e.GetY());
 		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetXOffset(), e.GetYOffset());
		return false;
	}

	bool ImGuiLayer::OnKeyPressdEvent(KeyPressedEvent& e)
	{
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) 
	{
		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		return false;
	}

	void ImGuiLayer::SetDarkThemeColors()
	{
		auto& style = ImGui::GetStyle();
		auto& colors = style.Colors;

		// Base Unreal-style grey tones
		colors[ImGuiCol_Text] = ImVec4{ 1.00f, 1.00f, 1.00f, 1.00f };
		colors[ImGuiCol_TextDisabled] = ImVec4{ 0.50f, 0.50f, 0.50f, 1.00f };
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.10f, 0.10f, 0.10f, 1.00f };
		colors[ImGuiCol_ChildBg] = ImVec4{ 0.13f, 0.13f, 0.13f, 1.00f };
		colors[ImGuiCol_PopupBg] = ImVec4{ 0.08f, 0.08f, 0.08f, 0.94f };
		colors[ImGuiCol_Border] = ImVec4{ 0.20f, 0.20f, 0.20f, 0.50f };
		colors[ImGuiCol_BorderShadow] = ImVec4{ 0.00f, 0.00f, 0.00f, 0.00f };

		// Frame (input fields, sliders, checkboxes...)
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.16f, 0.16f, 0.16f, 1.00f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.20f, 0.20f, 0.20f, 1.00f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.24f, 0.24f, 0.24f, 1.00f };

		// Title bar
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.09f, 0.09f, 0.09f, 1.00f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.12f, 0.12f, 0.12f, 1.00f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.09f, 0.09f, 0.09f, 0.75f };

		// Menu bar
		colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.12f, 0.12f, 0.12f, 1.00f };

		// Scrollbar
		colors[ImGuiCol_ScrollbarBg] = ImVec4{ 0.09f, 0.09f, 0.09f, 1.00f };
		colors[ImGuiCol_ScrollbarGrab] = ImVec4{ 0.30f, 0.30f, 0.30f, 1.00f };
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 0.40f, 0.40f, 0.40f, 1.00f };
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ 0.50f, 0.50f, 0.50f, 1.00f };

		// Checkmark / accent
		colors[ImGuiCol_CheckMark] = ImVec4{ 0.15f, 0.55f, 0.95f, 1.00f };
		colors[ImGuiCol_SliderGrab] = ImVec4{ 0.15f, 0.55f, 0.95f, 1.00f };
		colors[ImGuiCol_SliderGrabActive] = ImVec4{ 0.20f, 0.65f, 1.00f, 1.00f };

		// Button
		colors[ImGuiCol_Button] = ImVec4{ 0.20f, 0.20f, 0.20f, 1.00f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.15f, 0.55f, 0.95f, 0.80f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.55f, 0.95f, 1.00f };

		// Header (TreeNode, Selectable, CollapsingHeader)
		colors[ImGuiCol_Header] = ImVec4{ 0.18f, 0.18f, 0.18f, 1.00f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.15f, 0.55f, 0.95f, 0.60f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.55f, 0.95f, 0.90f };

		// Separator
		colors[ImGuiCol_Separator] = ImVec4{ 0.25f, 0.25f, 0.25f, 1.00f };
		colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.15f, 0.55f, 0.95f, 0.78f };
		colors[ImGuiCol_SeparatorActive] = ImVec4{ 0.15f, 0.55f, 0.95f, 1.00f };

		// Resize grip
		colors[ImGuiCol_ResizeGrip] = ImVec4{ 0.15f, 0.55f, 0.95f, 0.25f };
		colors[ImGuiCol_ResizeGripHovered] = ImVec4{ 0.15f, 0.55f, 0.95f, 0.67f };
		colors[ImGuiCol_ResizeGripActive] = ImVec4{ 0.15f, 0.55f, 0.95f, 0.95f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.13f, 0.13f, 0.13f, 1.00f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.15f, 0.55f, 0.95f, 0.80f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.18f, 0.18f, 0.18f, 1.00f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.09f, 0.09f, 0.09f, 1.00f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.13f, 0.13f, 0.13f, 1.00f };

		//// Docking (chỉ compile được khi build ImGui docking branch)
		//colors[ImGuiCol_DockingPreview] = ImVec4{ 0.15f, 0.55f, 0.95f, 0.70f };
		//colors[ImGuiCol_DockingEmptyBg] = ImVec4{ 0.08f, 0.08f, 0.08f, 1.00f };

		// Plot
		colors[ImGuiCol_PlotLines] = ImVec4{ 0.61f, 0.61f, 0.61f, 1.00f };
		colors[ImGuiCol_PlotLinesHovered] = ImVec4{ 0.15f, 0.55f, 0.95f, 1.00f };
		colors[ImGuiCol_PlotHistogram] = ImVec4{ 0.90f, 0.70f, 0.00f, 1.00f };
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4{ 1.00f, 0.60f, 0.00f, 1.00f };

		// Table
		colors[ImGuiCol_TableHeaderBg] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.00f };
		colors[ImGuiCol_TableBorderStrong] = ImVec4{ 0.25f, 0.25f, 0.25f, 1.00f };
		colors[ImGuiCol_TableBorderLight] = ImVec4{ 0.20f, 0.20f, 0.20f, 1.00f };
		colors[ImGuiCol_TableRowBg] = ImVec4{ 0.00f, 0.00f, 0.00f, 0.00f };
		colors[ImGuiCol_TableRowBgAlt] = ImVec4{ 1.00f, 1.00f, 1.00f, 0.03f };

		// Text selection / drag drop / nav
		colors[ImGuiCol_TextSelectedBg] = ImVec4{ 0.15f, 0.55f, 0.95f, 0.35f };
		colors[ImGuiCol_DragDropTarget] = ImVec4{ 0.15f, 0.55f, 0.95f, 0.90f };
		colors[ImGuiCol_NavHighlight] = ImVec4{ 0.15f, 0.55f, 0.95f, 1.00f };

		// Style vars
		style.WindowRounding = 4.0f;
		style.FrameRounding = 2.0f;
		style.PopupRounding = 2.0f;
		style.ScrollbarRounding = 3.0f;
		style.GrabRounding = 2.0f;
		style.TabRounding = 3.0f;

		style.WindowPadding = ImVec2(8.0f, 8.0f);
		style.FramePadding = ImVec2(6.0f, 4.0f);
		style.ItemSpacing = ImVec2(6.0f, 4.0f);
		style.WindowBorderSize = 1.0f;
		style.FrameBorderSize = 0.0f;
		style.TabBorderSize = 0.0f;
	}

}	