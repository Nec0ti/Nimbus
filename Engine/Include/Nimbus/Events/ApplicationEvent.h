#pragma once

#include "Nimbus/Events/Event.h"

namespace Nimbus {

    class NIMBUS_API WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(uint32 width, uint32 height)
            : m_Width(width), m_Height(height) {}

        uint32 GetWidth() const { return m_Width; }
        uint32 GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    private:
        uint32 m_Width, m_Height;
    };

    class NIMBUS_API WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NIMBUS_API AppTickEvent : public Event
    {
    public:
        AppTickEvent() = default;

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NIMBUS_API AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() = default;

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NIMBUS_API AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() = default;

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NIMBUS_API WindowFocusEvent : public Event
    {
    public:
        WindowFocusEvent() = default;

        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NIMBUS_API WindowLostFocusEvent : public Event
    {
    public:
        WindowLostFocusEvent() = default;

        EVENT_CLASS_TYPE(WindowLostFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class NIMBUS_API WindowMovedEvent : public Event
    {
    public:
        WindowMovedEvent(uint32 x, uint32 y)
            : m_WindowX(x), m_WindowY(y) {}

        uint32 GetX() const { return m_WindowX; }
        uint32 GetY() const { return m_WindowY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowMovedEvent: " << m_WindowX << ", " << m_WindowY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowMoved)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    private:
        uint32 m_WindowX, m_WindowY;
    };

}