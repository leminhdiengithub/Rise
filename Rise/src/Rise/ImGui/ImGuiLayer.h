#pragma once

#include"Rise/Layer.h"

#include"Rise/Events/ApplicationEvent.h"
#include"Rise/Events/KeyEvent.h"
#include"Rise/Events/MouseEvent.h"

namespace Rise 
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End(); 
		void SetDarkThemeColors();

	private:

	};
}