#pragma once


#ifdef HZ_PLATFORM_WINDOWS
	//��δ����ǹ���DLL�����͵���Ĺؼ����֣������˿���Ŀ�������ı�������
	#ifdef HZ_BUILD_DLL
	//__declspec(dllexport)��΢���ض�����չ������ָʾ�������÷��ţ�����������������Ҫ�������Ա�����Ӧ�ó������ͨ��DLLʹ����Щ����
		#define HAZEL_API __declspec(dllexport) 
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#error Hazel only supports Windows!
#endif

#define BIT(x)  (1 << x)
