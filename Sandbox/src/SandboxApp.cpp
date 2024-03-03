#include <FirstEngine.h>

#include "imgui/imgui.h"

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
		if (FirstEngine::Input::IsKeyPressed(FE_KEY_TAB))
			FE_TRACE("Tab Key is pressed!");
	}


	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}


	void OnEvent(FirstEngine::Event& event) override
	{
		if (event.GetEventType() == FirstEngine::EventType::KeyPressed)
		{
			FirstEngine::KeyPressedEvent& e = (FirstEngine::KeyPressedEvent&)event;
			FE_TRACE("{0}",(char)e.GetKeyCode());
		}
	}
};


class Sandbox : public FirstEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
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
