#include "rscph.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Rise/Log.h"

namespace Rise
{
    Application::Application() {}
    Application::~Application() {}

    void Application::Run()
    {
        WindowResizeEvent e(1920, 1080);

        if (e.IsInCategory(EventCategoryApplication))
        {
            RS_CORE_TRACE(e.ToString());
        }

        while (true);
    }
}