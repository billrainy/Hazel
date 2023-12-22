#pragma once
#include "Core.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();

		virtual ~Application();  //Hazel::Application class will be inhereted by Sandbox::Application, therefore the deconstructor should be virtual.
		
		void Run();
	};

	//To be defined in CLIENT
	Hazel::Application* CreateApplication();
}


