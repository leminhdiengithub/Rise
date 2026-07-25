#pragma once

#include "Rise/Core.h"
#include "rscph.h"
#include <spdlog/fmt/ostr.h>

namespace Rise
{
	/* Cac su kien trong Rise hien dang bi chan, nghia la khi mot su kien xay ra
	, no ngay lap tuc duoc gui di va xu ly ngay lap tuc
	.Trong tuong lai, mot chien luoc tot hon co the la dem cac su kien trong mot bus su kien
	va xu ly chung trong phan "su kien" cua giai doan cap nhat.*/

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLost, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyRealeased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BTT(0),
		EventCategoryInput			= BTT(1),
		EventCategoryKeyboard		= BTT(2),
		EventCategoryMouse			= BTT(3),
		EventCattegoryButton		= BTT(4)
	};
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type; }\
								virtual EventType GetEventType() const override {return GetStaticType(); }\
								virtual const char* GetName() const override {return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category; }

	class RISE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual ~Event() = default;

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return  GetName(); }
		
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
template<> struct fmt::formatter<Rise::Event> : fmt::ostream_formatter {};