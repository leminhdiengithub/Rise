#pragma once

#include"Rise/Layer.h"

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

	private:

	};
}