#pragma once

#include "Rise/Core.h"
#include "Rise/Events/Event.h"

namespace Rise
{
	class RISE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");	
		
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}

/*name (trong .h) và debugName (trong .cpp) là cùng một tham số (không phải 2 object khác nhau) 
— nó chỉ là alias(bí danh) tạm thời tới giá trị truyền vào. 
Còn m_DebugName là bản copy độc lập, được tạo ra đúng 1 lần để đảm bảo nó vẫn "sống" 
và hợp lệ ngay cả sau khi tham số tạm thời kia đã biến mất.*/