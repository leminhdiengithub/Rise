#pragma once

#include "Core.h"
#include"Events/Event.h"
#include"Window.h"

namespace Rise
{
	class  RISE_API Application
	{
	public:
		Application();
		virtual ~Application(); /*virtual đảm bảo gọi đúng destructor theo thứ tự, cụ thể: Sandbox -> Application*/

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLINET 
	Application* CreateApplication();
}
