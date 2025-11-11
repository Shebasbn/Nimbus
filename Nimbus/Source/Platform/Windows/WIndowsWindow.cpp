#include "nbpch.h"
#include "WindowsWindow.h"
#include "Core/Event/ApplicationEvent.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/MouseEvent.h"

namespace Nimbus
{
	static bool s_WindowClassInitialized = false;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		WindowsWindow* window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		switch (message)
		{
			case WM_NCCREATE:
			{
				/*LPCREATESTRUCT param = reinterpret_cast<LPCREATESTRUCT>(lParam);
				window = reinterpret_cast<WindowsWindow*>(param->lpCreateParams);
				SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));*/
			} break;
			case WM_CREATE:
			{

			} break;
			case WM_DESTROY: PostQuitMessage(0); break;
			case WM_CLOSE:
			{
				if (window)
				{
					WindowCloseEvent event;
					window->HandleEvent(event);
				}
				return 0;
			} break;
			case WM_SIZE:
			{
				if (window)
				{
					unsigned int width = LOWORD(lParam);
					unsigned int height = HIWORD(lParam);
					WindowResizeEvent e(width, height);
					window->HandleEvent(e);
				}
				return 0;
			} break;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		m_IsRunning = Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	bool WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		NB_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		m_Instance = GetModuleHandle(nullptr);

		if (!s_WindowClassInitialized)
		{
			WNDCLASS wndClass = {};
			wndClass.lpszClassName = L"NimbusWindowClass";
			//wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			//wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			//wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
			wndClass.lpfnWndProc = WndProc;
			wndClass.hInstance = m_Instance;

			s_WindowClassInitialized = RegisterClass(&wndClass);
			NB_CORE_ASSERT(s_WindowClassInitialized, "Could Not Register Window Class!");
		}

		RECT rect = { 0, 0, static_cast<LONG>(m_Data.Width), static_cast<LONG>(m_Data.Height) };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		m_Window = CreateWindow(
			L"NimbusWindowClass", 
			L"Nimbus Engine", 
			WS_OVERLAPPEDWINDOW, 
			CW_USEDEFAULT, CW_USEDEFAULT, 
			rect.right - rect.left, 
			rect.bottom - rect.top,
			0, 0, m_Instance, this);


		if (!m_Window)
		{
			NB_CORE_CRITICAL("Create Window Has Failed!");
			return false;
		}

		SetWindowLongPtr(m_Window, GWLP_USERDATA, (LONG_PTR)this);

		AllowSetForegroundWindow(ASFW_ANY);
		ShowWindow(m_Window, SW_SHOW);
		UpdateWindow(m_Window);
		SetForegroundWindow(m_Window);
		SetFocus(m_Window);
		SetVSync(true);

		/*if (!AllowSetForegroundWindow(ASFW_ANY)) { NB_CORE_ERROR("Allow Set Window Foreground Has Failed!"); return false; }
		if (!ShowWindow(m_Window, SW_SHOW)) { NB_CORE_ERROR("Show Window Has Failed!"); return false; }
		if (!UpdateWindow(m_Window)) { NB_CORE_ERROR("Update Window Has Failed!"); return false; }
		if (!SetForegroundWindow(m_Window)) { NB_CORE_ERROR("Set Window Foreground Has Failed!"); return false; }
		if (!SetFocus(m_Window)) { NB_CORE_ERROR("Set focus Has Failed!"); return false; }*/
	}

	void WindowsWindow::OnUpdate()
	{
		MSG msg;
		while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WindowsWindow::ResizeWindow(unsigned int width, unsigned int height)
	{
		m_Data.Width = width;
		m_Data.Height = height;
	}

	void WindowsWindow::Shutdown()
	{
		DestroyWindow(m_Window);
		m_Window = nullptr;
		m_IsRunning = false;
	}

}