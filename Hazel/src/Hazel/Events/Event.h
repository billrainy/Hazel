#pragma once

#include "Hazel/Core.h"  //premake�ű��У�ͨ��includedirs�ؼ���Ϊ"Hazel.proj"�ṩ��ͷ�ļ���·����Hazel/src(������ͷ�ļ��ķ��������¼��ݵģ���ֻ�е�ͷ�ļ��ڱ��ļ��ĸ�·����ʱ������Ҫʹ�ø÷��������򣬿�ֱ�Ӵӱ��ļ���·����������)

#include <string>
#include <functional>

namespace Hazel {

	enum class EventType   // enum class + ö������->����ö�ٳ���ʱ��Ҫ��ö��������Ϊ������
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
		EventCategoryApplication = BIT(0),  // BIT(x)����Ϊ"Core.h"�ж����macro
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

		//������Ԫ��--�¼�������������Ҫ�����¼��ĳ�Ա������m_Handled
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

	class EventDispatcher  //Ϊʲô�˴�û�н��¼������������.dll?->�漰��Event.h������������Ӧ�öˡ�
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;  //������һ���ص�����ģ�壬���ຯ������һ���¼����͵�������Ϊ����������һ������ֵ

	public:
		EventDispatcher(Event& event): m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)  //��ʵ�ϣ��˴���func��δ���壬������֮ǰ�����ģ���֪���ú���Ӧ����һ���¼����͵�������Ϊ����������һ������ֵ
		{
			if (m_Event.GetEventType() == T.GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);  //ǿ������ת��������̬����ģ���������->����������
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
		//�ص㣺�˴�����Ա��������Ϊ�������ͣ���Ϊ�˱����ʼ��(initialization)�����ñ���ʱ��
		//����object slicing������(only the base class part of the derived class object is retained when assigned to a base class object);
		//�˴�ʵ����ͨ����̬����ʵ���˸��������������Ĺ��ܣ��Ӷ���ʹ�ø����ñ������ö�̬�ĳ�Ա�����������м�virtual���Σ�ʱ�����Ե�������ĳ�Ա����(i.e., m_Event.GetEventType())��
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}
