#include "event.h"
#include <deque>


namespace os
{
    namespace
    {
        auto get_event_queue() noexcept -> std::deque<event>&
        {
            static std::deque<event> event_queue;
            return event_queue;
        }

        auto pop_event(event& e) noexcept -> bool
        {
            auto& event_queue = get_event_queue();
            // Pop the first event of the queue, if it is not empty
            if(!event_queue.empty())
            {
                e = event_queue.front();
                event_queue.pop_front();
                return true;
            }
            return false;
        }
    }

    auto poll_event(event& e) noexcept -> bool
    {
        return pop_event(e);
    }

    void push_event(const event& e)
    {
        get_event_queue().emplace_back(e);
    }
    void push_event(event&& e)
    {
        get_event_queue().emplace_back(std::move(e));
    }
}
