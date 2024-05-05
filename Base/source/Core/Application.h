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
            inline void ToggleDebug() { m_debugMode = !m_debugMode; }

            void Run();
            void Quit();

        protected:
            virtual void OnUpdate() {}
            virtual void OnRender() {}
            virtual void OnUIRender() {}

            void SetClearColor(float r, float g, float b);

        private:
            bool m_running = true;
            bool m_debugMode = false;
            Window m_window;

        private:
            static Application* s_instance;
        };
    }
}
