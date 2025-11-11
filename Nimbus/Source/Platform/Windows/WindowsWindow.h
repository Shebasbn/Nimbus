#pragma once

#include "Core/Window.h"

namespace Nimbus
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		void ResizeWindow(unsigned int width, unsigned int height) override;

		inline void HandleEvent(Event& event) { if (m_Data.EventCallback) { m_Data.EventCallback(event); } }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		inline void SetVSync(bool enabled) override { m_Data.VSync = true; }
		inline bool IsVSync() const override { return m_Data.VSync; }
		inline bool IsRunning() const override { return m_IsRunning; }

	private:
		virtual bool Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		HWND m_Window;
		HINSTANCE m_Instance;
		bool m_IsRunning = false;
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}