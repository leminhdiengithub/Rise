#include "rscph.h"
#include "Application.h"

#include "Rise/Log.h"

namespace Rise
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this , std::placeholders::_1)

    Application::Application() 
    {
        m_Window = std::unique_ptr<Window>(Window::Create()); /* Application (cấp cao) → phụ thuộc vào Window (abstraction)*/
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application() {}

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispathcer(e);
        dispathcer.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        RS_CORE_INFO( "{0}", e.ToString());
    }
    void Application::Run()
    {

        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;

        return true;
    }

}