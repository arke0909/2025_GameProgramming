#pragma once
#include "pch.h"

template<typename... Args>
class Event
{
public:
    using Handler = std::function<void(Args...)>;

    void Subscribe(Handler handler)
    {
        _handlers.push_back(handler);
    }

    void Unsubscribe(Handler handler)
    {
        _handlers.erase(
            std::remove(_handlers.begin(), _handlers.end(), handler),
            _handlers.end());
    }

    void Raise(Args... args)
    {
        for (auto& handler : _handlers)
        {
            if (handler)
                handler(args...);
        }
    }

private:
    std::vector<Handler> _handlers;
};

