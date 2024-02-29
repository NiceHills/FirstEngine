#pragma once

#ifdef FE_PLATFORM_WINDOWS

extern FirstEngine::Application* FirstEngine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = FirstEngine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif