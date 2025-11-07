#pragma once

#include "Core.h"

namespace Nimbus
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

