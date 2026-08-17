#include "rscph.h"
#include "Application.h"

#include "Rise/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Rise
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this , std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application() 
    {
        RS_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;                              

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

    }

    Application::~Application() 
    {
          
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispathcer(e);
        dispathcer.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        RS_CORE_INFO( "{0}", e.ToString());

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
                break;
        }
    }
    void Application::Run()
    {

        while (m_Running)
        {
            glClear(GL_COLOR_BUFFER_BIT);

            RS_CORE_TRACE("Application::Run - loop tick");
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            auto [x, y] = Input::GetMousePosition();
            RS_CORE_TRACE("{0}, {1}", x, y);
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        RS_CORE_WARN("OnWindowClose triggered!");
        m_Running = false;

        return true;
    }

}