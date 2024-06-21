#pragma once
#include "Core.h"
//#include "Events/Event.h"  //疑问：如果此处引入Event.h头文件的目的仅为保证Application.cpp中正确实例化Event的派生类对象(e.g., WindowResizeEvent)，那么是否此处可以无需显式地执行该引用操作？既然在派生类的头文件类声明中已经引用过Event.h?

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();

		virtual ~Application();  //Hazel::Application class will be inhereted by Sandbox::Application, therefore the deconstructor should be virtual.
		
		void Run();
	};

	//To be defined in CLIENT, so this function is declared outside the above class -> thus outside Hazel.dll/.lib files
	Hazel::Application* CreateApplication();
}


