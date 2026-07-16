#pragma once

#include "Event.h"

namespace Rise {

	// =========================================================
	// MouseMovedEvent
	// Kích hoạt khi người dùng DI CHUYỂN chuột
	// Lưu tọa độ X, Y của chuột trên màn hình
	// =========================================================
	class RISE_API MouseMovedEvent : public Event
	{
	public:
		// Constructor: nhận vào tọa độ x, y của chuột
		// Dùng initializer list để gán vào m_MouseX, m_MouseY
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {
		}

		// Trả về tọa độ X hiện tại của chuột
		inline float GetX() const { return m_MouseX; }

		// Trả về tọa độ Y hiện tại của chuột
		inline float GetY() const { return m_MouseY; }

		// Debug: in ra thông tin event dạng string
		// VD: "MouseMovedEvent: 512, 300"
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		// Macro tự động generate hàm GetStaticType(), GetEventType(), GetName()
		EVENT_CLASS_TYPE(MouseMoved)

			// Macro gán category: vừa là Mouse vừa là Input
			// Cho phép filter event theo nhóm
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY; // Tọa độ chuột hiện tại
	};


	// =========================================================
	// MouseScrolledEvent
	// Kích hoạt khi người dùng CUỘN chuột (scroll wheel)
	// Lưu offset X (cuộn ngang) và Y (cuộn dọc)
	// =========================================================
	class RISE_API MouseScrolledEvent : public Event
	{
	public:
		// xOffset: cuộn ngang (shift + scroll)
		// yOffset: cuộn dọc (scroll thông thường)
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {
		}

		// Trả về lượng cuộn theo trục X
		inline float GetXOffset() const { return m_XOffset; }

		// Trả về lượng cuộn theo trục Y
		inline float GetYOffset() const { return m_YOffset; }

		// Debug: VD: "MouseScrolledEvent: 0, -1"
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffset, m_YOffset; // Lượng cuộn theo X và Y
	};


	// =========================================================
	// MouseButtonEvent (Abstract Base Class)
	// Class cha cho tất cả sự kiện CLICK chuột
	// KHÔNG dùng trực tiếp → constructor để ở protected
	// Không có EVENT_CLASS_TYPE vì đây là class trừu tượng
	// =========================================================
	class RISE_API MouseButtonEvent : public Event
	{
	public:
		// Trả về mã nút chuột được nhấn
		// VD: 0 = Left, 1 = Right, 2 = Middle
		inline int GetMouseButton() const { return m_Button; }

		// Chỉ có CATEGORY, không có TYPE
		// Vì subclass sẽ tự định nghĩa TYPE của mình
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		// Constructor protected → chỉ subclass mới được gọi
		// Không ai có thể tạo MouseButtonEvent trực tiếp
		MouseButtonEvent(int button)
			: m_Button(button) {
		}

		int m_Button; // Mã nút chuột (button code)
	};


	// =========================================================
	// MouseButtonPressedEvent
	// Kích hoạt khi người dùng NHẤN (press) nút chuột
	// Kế thừa từ MouseButtonEvent
	// =========================================================
	class RISE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		// Gọi constructor của MouseButtonEvent để lưu button code
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {
		}

		// Debug: VD: "MouseButtonPressedEvent: 0" (chuột trái)
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
			// Không cần EVENT_CLASS_CATEGORY vì đã kế thừa từ MouseButtonEvent
	};


	// =========================================================
	// MouseButtonReleasedEvent
	// Kích hoạt khi người dùng THẢ (release) nút chuột
	// Kế thừa từ MouseButtonEvent
	// =========================================================
	class RISE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		// Gọi constructor của MouseButtonEvent để lưu button code
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {
		}

		// Debug: VD: "MouseButtonReleasedEvent: 0" (chuột trái)
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

} // namespace Hazel