#pragma once
#include "Core.h"
//#include "Events/Event.h"  //���ʣ�����˴�����Event.hͷ�ļ���Ŀ�Ľ�Ϊ��֤Application.cpp����ȷʵ����Event�����������(e.g., WindowResizeEvent)����ô�Ƿ�˴�����������ʽ��ִ�и����ò�������Ȼ���������ͷ�ļ����������Ѿ����ù�Event.h?

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


