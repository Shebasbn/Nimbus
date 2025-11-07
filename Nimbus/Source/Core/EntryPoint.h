#pragma once

#ifdef NB_PLATFORM_WINDOWS

extern Nimbus::Application* Nimbus::CreateApplication();

int main(int argc, char** argv)
{
	Nimbus::Log::Init();
	NB_CORE_WARN("Initialized Log!");
	int a = 5;
	NB_INFO("Hello, welcome to the Nimbus Engine! Var={0}!", a);

	auto app = Nimbus::CreateApplication();
	app->Run();
	delete app;
}

#else
#endif