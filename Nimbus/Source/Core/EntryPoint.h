#pragma once

#ifdef NB_PLATFORM_WINDOWS

extern Nimbus::Application* Nimbus::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Nimbus::CreateApplication();
	app->Run();
	delete app;
}

#else
#endif