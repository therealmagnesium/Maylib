#pragma once
#include "Core/Base.h"
#include "Graphics/Window.h"
#include <string>

using namespace Maylib::Graphics;

namespace Maylib
{
    namespace Core
    {
        struct AppInfo
        {
            std::string name;
            std::string author;
            u32 screenWidth;
            u32 screenHeight;
            bool vsync = true;
        };

        class Application
        {
        public:
            Application(const AppInfo& info);
            ~Application();

            static inline Application* Get() { return s_instance; }

            void Run();
            void Quit();

        protected:
            virtual void OnUpdate() {}
            virtual void OnUIRender() {}

        private:
            bool m_running = true;
            Window m_window;

        private:
            static Application* s_instance;
        };
    }
}
