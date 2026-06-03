#pragma once

#ifdef RS_PLATFORM_WINDOWS

extern Rise::Application* Rise::CreateApplication();

int main(int argc, char* argv)
{
    Rise::Log::Init();
    RS_CORE_WARN("Initialized Log!");
    int a = 5;
    RS_CORE_INFO("Hi Var={0}", a);

    auto app = Rise::CreateApplication();
    app->Run();
    delete app;
}
#endif 
