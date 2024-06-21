#pragma once


#ifdef HZ_PLATFORM_WINDOWS
	//这段代码是管理DLL导出和导入的关键部分，它简化了跨项目共享代码的编译配置
	#ifdef HZ_BUILD_DLL
	//__declspec(dllexport)是微软特定的扩展，用于指示编译器该符号（函数、类或变量）需要导出，以便其他应用程序可以通过DLL使用这些符号
		#define HAZEL_API __declspec(dllexport) 
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#error Hazel only supports Windows!
#endif

#define BIT(x)  (1 << x)
