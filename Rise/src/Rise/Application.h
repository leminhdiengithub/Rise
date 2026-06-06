#pragma once

#include "Core.h"
#include"Events/Event.h"

namespace Rise
{
	class  RISE_API Application
	{
	public:
		Application();
		virtual ~Application(); /*virtual đảm bảo gọi đúng destructor theo thứ tự, cụ thể: Sandbox -> Application*/

		void Run();
	};

	// To be defined in CLINET 
	Application* CreateApplication();
}
