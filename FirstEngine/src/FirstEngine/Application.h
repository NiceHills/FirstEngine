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

	//��Client�ж���
	Application* CreateApplication();
}