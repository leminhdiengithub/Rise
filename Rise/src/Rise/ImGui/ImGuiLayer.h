#pragma once

#include"Rise/Layer.h"

#include"Rise/Events/ApplicationEvent.h"
#include"Rise/Events/KeyEvent.h"
#include"Rise/Events/MouseEvent.h"

namespace Rise 
{
	class RISE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

		void SetDarkThemeColors();

	private:

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMoveEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressdEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		//bool OnKeyTypeEvent(OnKeyTypeEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	};
}