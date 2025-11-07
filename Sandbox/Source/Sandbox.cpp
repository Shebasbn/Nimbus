#include <Nimbus.h>

class Sandbox : public Nimbus::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}
};

Nimbus::Application* Nimbus::CreateApplication()
{
	return new Sandbox();
}