#pragma once

#include "Core.h"
#include "Core/Window.h"
#include "Event/ApplicationEvent.h"

namespace Nimbus
{
	class Application
	{
	public:
		Application() = default;
		virtual ~Application();

		virtual bool Init();
		void Run();

		virtual void OnEvent(Event& e);
		inline virtual bool OnWindowClose(WindowCloseEvent& e) { m_IsRunning = false; return true; }
		inline virtual bool OnWindowResize(WindowResizeEvent& e) { m_Window->ResizeWindow(e.GetWidth(), e.GetHeight()); return true; }

		inline bool IsRunning() { return m_IsRunning; }

	private:
		std::shared_ptr<Window> m_Window;
		bool m_IsRunning = false;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

