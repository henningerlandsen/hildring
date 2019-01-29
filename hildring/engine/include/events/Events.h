#pragma once

#include "util/LifetimeToken.h"

#include <algorithm>
#include <vector>

namespace events {
namespace detail {
    template <class EventType>
    class EventRegistry {
    private:
        template <class Object, void (Object::*Method)(const EventType&)>
        static void invoke(void* instance, const EventType& eventData)
        {
            (static_cast<Object*>(instance)->*Method)(eventData);
        }

        static bool contains(void* instance)
        {
            return std::find_if(begin(listeners), end(listeners), EntryContains(instance)) != listeners.end();
        }

    public:
        template <class Object, void (Object::*Method)(const EventType&)>
        static void addListener(Object* instance)
        {
            if (!contains(instance)) {
                listeners.emplace_back(instance, &invoke<Object, Method>);
            }
        }

        static void dispatch(const EventType& eventData)
        {
            for (auto&& l : listeners) {
                l.function(l.instance, eventData);
            }
        }

        static void removeListener(void* instance)
        {
            listeners.erase(
                std::remove_if(begin(listeners), end(listeners), EntryContains(instance)),
                end(listeners));
        }

    private:
        struct Entry {
            using Fn = void (*)(void*, const EventType&);

            Entry(void* instance, Fn function)
                : instance(instance)
                , function(function)
            {
            }

            void* instance;
            Fn function;
        };

        struct EntryContains {
            EntryContains(void* instance)
                : instance(instance)
            {
            }

            bool operator()(const Entry& e)
            {
                return e.instance == instance;
            }

            void* instance;
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

template <class EventType, class Object>
void unsubscribe(const Object& instance)
{
    detail::EventRegistry<EventType>::removeListener(instance);
}

template <class EventType, class Object, void (Object::*Method)(const EventType&) = &Object::event>
util::LifetimeToken subscription(Object* instance)
{
    subscribe<EventType, Object, Method>(instance);
    return { [instance]() { unsubscribe<EventType>(instance); } };
}

template <class EventType>
void dispatch(const EventType& eventData)
{
    detail::EventRegistry<EventType>::dispatch(eventData);
}

}
