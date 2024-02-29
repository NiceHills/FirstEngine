#pragma once
#include "Core.h"


namespace FirstEngine{

	class FE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//在Client中定义
	Application* CreateApplication();
}