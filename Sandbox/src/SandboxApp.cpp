#include <FirstEngine.h>
#include <iostream>

class Sandbox : public FirstEngine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

FirstEngine::Application* FirstEngine::CreateApplication()
{
	std::cout << "Hello world" << std::endl;
	return new Sandbox();
}
