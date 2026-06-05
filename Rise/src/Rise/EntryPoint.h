#pragma once

#ifdef RS_PLATFORM_WINDOWS

extern Rise::Application* Rise::CreateApplication();

int main(int argc, char* argv)
{
    Rise::Log::Init();
    RS_CORE_WARN("Initialized Log!");
    int a = 5;
    RS_INFO("Hello Var={0}", a);

    auto app = Rise::CreateApplication();
    app->Run();
    delete app;
}
#endif 

/*
extern : khai báo một hàm được định nghĩa ở file khác.
*/ 