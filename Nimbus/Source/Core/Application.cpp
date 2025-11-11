#include <nbpch.h>
#include "Application.h"
#include "Core/Log.h"

namespace Nimbus
{
	Application::~Application()
	{
	}

	bool Application::Init()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_IsRunning = m_Window->IsRunning();
		m_Window->SetEventCallback(NB_BIND_EVENT_FN(Application::OnEvent));
		return true;
	}

	void Application::OnEvent(Event& e)
	{
		NB_CORE_TRACE("{}", e.ToString());
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(NB_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(NB_BIND_EVENT_FN(Application::OnWindowResize));
	}

	void Application::Run()
	{
		while (IsRunning())
		{
			m_Window->OnUpdate();
		}
	}
		
}
