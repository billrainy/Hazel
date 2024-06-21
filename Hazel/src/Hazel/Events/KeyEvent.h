#pragma once

#include "Event.h"

#include <sstream>

namespace Hazel {
	class HAZEL_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keycode) m_Keycode(keycode) :{}
		int m_KeyCode;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount) KeyEvent(keycode), m_RepeatCount(repeatCount) :{} 
		/*�ص㣺����̳���������Ĺ��캯��ʱ�����ó�Ա��ʼ���б���ʽ��Ƕ�׵��û���Ĺ��캯����
		���򣬽��Զ����û����Ĭ�Ϲ��캯�����������������Ƕ�׵Ļ������ĳ�Ա�����ĳ�ʼ����ֵʧ�ܡ�*/

		inline int GetRepeatCount() {return m_RepeatCount;}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent:" << m_KeyCode << "(" << m_RepeatCount << "repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}