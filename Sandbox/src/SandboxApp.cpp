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
        RS_INFO("ExampleLayer::Update");
    }

    void OnEvent(Rise::Event& event) override
    {
        RS_TRACE( "{0}", event);
    }
};

class Sandbox : public Rise::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

Rise::Application* Rise::CreateApplication()
{
    return new Sandbox();
}