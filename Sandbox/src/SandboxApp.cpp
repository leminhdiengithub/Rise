#include "Rise/Rise.h"

class ExampleLayer : public Rise::Layer
{
public:
    ExampleLayer()
        :Layer("Exalmpler") 
    {
    }

    void OnUpdate() override
    {
        if (Rise::Input::IsKeyPressed(RS_KEY_TAB))
            RS_TRACE("Tab key is Pressed !");
    }

    void OnEvent(Rise::Event& event) override
    {
        if (event.GetEventType() == Rise::EventType::KeyPressed)
        {
            Rise::KeyPressedEvent& e = (Rise::KeyPressedEvent&)event;
            RS_TRACE("{0}", (char)e.GetKeyCode());
        }
    }
};

class Sandbox : public Rise::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new Rise::ImGuiLayer());
    }

    ~Sandbox()
    {

    }
};

Rise::Application* Rise::CreateApplication()
{
    return new Sandbox();
}