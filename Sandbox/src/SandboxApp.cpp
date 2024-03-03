#include <FirstEngine.h>
#include <iostream>

class ExampleLayer : public FirstEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//FE_INFO("ExampleLayer::Update");
	}

	void OnEvent(FirstEngine::Event& event) override
	{
		FE_TRACE("{0}", event);
	}
};


class Sandbox : public FirstEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		Pushoverlay(new FirstEngine::ImGuiLayer());
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
