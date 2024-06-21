#pragma once

#include "Hazel/Core.h"  //premake脚本中，通过includedirs关键字为"Hazel.proj"提供了头文件的路径：Hazel/src(该引入头文件的方法是向下兼容的，即只有当头文件在本文件的父路径中时，才需要使用该方法；否则，可直接从本文件的路径向下引用)

#include <string>
#include <functional>

namespace Hazel {

	enum class EventType   // enum class + 枚举类名->调用枚举常量时需要将枚举类名作为作用域
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory 
	{
		None = 0,
		EventCategoryApplication = BIT(0),  // BIT(x)函数为"Core.h"中定义的macro
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) inline static EventType GetStaticType() {return EventType::##type;}\
	virtual EventType GetEventType() const override { return GetStaticType();}\
	virtual const char* GetName() const override { return #type; }
	// 'override' keyword helps catch ERRORS at complie time if there's a mismatch in
	// function signatures or if there's no function in the base class to override


#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override{return category;}


	class HAZEL_API Event
	{

		//声明友元类--事件发包器类型需要访问事件的成员变量：m_Handled
		friend class EventDispatcher;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	class EventDispatcher  //为什么此处没有将事件发包器打包进.dll?->涉及到Event.h将怎样被用于应用端。
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;  //定义了一个回调函数模板，此类函数接受一个事件类型的引用作为参数并返回一个布尔值

	public:
		EventDispatcher(Event& event): m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)  //事实上，此处的func还未定义，但是由之前定义的模板可知，该函数应接受一个事件类型的引用作为参数并返回一个布尔值
		{
			if (m_Event.GetEventType() == T.GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);  //强制类型转换：（动态联编的）基类类型->派生类类型
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
		//重点：此处将成员变量声明为引用类型，是为了避免初始化(initialization)该引用变量时，
		//出现object slicing的问题(only the base class part of the derived class object is retained when assigned to a base class object);
		//此处实际上通过动态联编实现了父类引用子类对象的功能，从而在使用该引用变量调用多态的成员函数（基类中加virtual修饰）时，得以调用子类的成员函数(i.e., m_Event.GetEventType())。
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}
