#pragma once

#include <vector>

namespace Events {
namespace detail {
    template <class EventType>
    class EventRegistry {
    private:
        template <class Object, void (Object::*Method)(const EventType&)>
        static void invoke(void* instance, const EventType& eventData)
        {
            (static_cast<Object*>(instance)->*Method)(eventData);
        }

    public:
        template <class Object, void (Object::*Method)(const EventType&)>
        static void addListener(Object* instance)
        {
            Entry e;
            e.instance = instance;
            e.function = &invoke<Object, Method>;
            listeners.push_back(e);
        }

        static void dispatch(const EventType& eventData)
        {
            for (auto&& l : listeners) {
                l.function(l.instance, eventData);
            }
        }

    private:
        struct Entry {
            using Fn = void (*)(void*, const EventType&);
            void* instance;
            Fn function;
        };

        static std::vector<Entry> listeners;
    };

    template <class EventType>
    std::vector<typename EventRegistry<EventType>::Entry> EventRegistry<EventType>::listeners = {};
}

template <class EventType, class Object, void (Object::*Method)(const EventType&) = &Object::event>
void subscribe(Object* instance)
{
    detail::EventRegistry<EventType>::template addListener<Object, Method>(instance);
}

template <class EventType>
void dispatch(EventType&& eventData)
{
    detail::EventRegistry<EventType>::dispatch(eventData);
}

template <class EventType>
void dispatch(const EventType& eventData)
{
    detail::EventRegistry<EventType>::dispatch(eventData);
}
}
