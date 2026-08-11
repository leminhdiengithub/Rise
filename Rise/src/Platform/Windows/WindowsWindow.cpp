#include "rscph.h"
#include "WindowsWindow.h"

#include"Rise/Events/ApplicationEvent.h"
#include"Rise/Events/MouseEvent.h"
#include"Rise/Events/KeyEvent.h"

#include <glad/glad.h>

namespace Rise {
	static bool s_GLWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		RS_CORE_ERROR("GLWF Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}
	
	WindowsWindow::~WindowsWindow()
	{ 
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		RS_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLWInitialized)
		{
			int success = glfwInit();
			RS_CORE_ASSERT(success, "Could mot intialize GLFW! ");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr );
		RS_CORE_ASSERT(m_Window, "Failed to create GLFW window!");
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RS_CORE_ASSERT(status, "Failed to initialize Glad !");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Set GLFW callback
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
				// Lambda này KHÔNG capture gì cả ([]) -> tự động convert thành 
				// function pointer thuần C, đúng kiểu GLFW yêu cầu.
				// Vì không capture, nên không có "this" -> phải lấy state qua user pointer.

				// Lấy lại con trỏ WindowData đã gắn từ trước bằng glfwSetWindowUserPointer(m_Window, &m_Data)
				// glfwGetWindowUserPointer trả về void*, nên phải ép kiểu (cast) về WindowData*
				// rồi dereference (*) để lấy reference tới object WindowData thật sự.
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				// Cập nhật lại width/height nội bộ của Window,
				// để sau này gọi Window::GetWidth()/GetHeight() luôn trả về giá trị mới nhất
				data.Width = width;
				data.Height = height;
				// Tạo một event object đại diện cho việc resize,
				//WindowResizeEvent kế thừa từ class Event (theo hệ thống Event bạn đã dựng)
				WindowResizeEvent event(width, height);
				// Gọi hàm callback đã được Application đăng ký trước đó
			   // (thường là Application::OnEvent, được bind qua SetEventCallback)
			   // -> đây chính là bước "bắn" event ra khỏi tầng Window, đẩy lên tầng Application
				data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent envet;
				data.EventCallback(envet);
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});
		
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS: 
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{

						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xoffset, (float)yoffset);
				data.EventCallback(event);
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xpos, (float)ypos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);

	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
		
			glfwSwapInterval(1);
		
		else
		
			glfwSwapInterval(0);
		
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}