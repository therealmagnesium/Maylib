#pragma once
#include "Core/Base.h"
#include "Graphics/Camera.h"
#include "Graphics/Window.h"

#include <SDL2/SDL_mouse.h>
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
            inline bool DebugEnabled() { return m_debugMode; }
            inline bool FullscreenEnabled() { return m_fullscreen; }
            inline AppInfo& GetInfo() { return m_info; }
            inline Window* GetWindow() { return &m_window; }
            inline Camera* GetPrimaryCamera() { return m_primaryCamera; }

            inline void ToggleDebug() { m_debugMode = !m_debugMode; }
            inline void ToggleFullscreen() { m_fullscreen = !m_fullscreen; }
            inline void ShowCursor(bool toggle) { SDL_ShowCursor(toggle); }
            inline void SetPrimaryCamera(Camera* camera) { m_primaryCamera = camera; }

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
            bool m_fullscreen = false;

            Window m_window;
            AppInfo m_info;
            Camera* m_primaryCamera = NULL;

        private:
            static Application* s_instance;
        };
    }
}
