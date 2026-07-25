#pragma once

#include "Core.h"

#include"Window.h"
#include"Events/Event.h"
#include "LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "Layer.h"

namespace Rise
{
	class  RISE_API Application
	{
	public:
		Application();
		virtual ~Application(); /*virtual đảm bảo gọi đúng destructor theo thứ tự, cụ thể: Sandbox -> Application*/

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLINET 
	Application* CreateApplication();
}
