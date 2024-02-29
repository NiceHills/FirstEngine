#pragma once

#ifdef FE_PLATFORM_WINDOWS

extern FirstEngine::Application* FirstEngine::CreateApplication();

int main(int argc, char** argv)
{
	FirstEngine::Log::Init();
	FE_CORE_WARN("Initialized Log!");
	int a = 5;
	FE_INFO("Hello!,Var = {0}",a);

	auto app = FirstEngine::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif