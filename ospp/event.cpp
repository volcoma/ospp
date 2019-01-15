#include "event.h"
#include <cstring>
#include <deque>

#if defined(SDL_BACKEND)
#include "impl/sdl/event.hpp"
#define impl detail::sdl
#elif defined(MML_BACKEND)
#include "impl/mml/event.hpp"
#define impl detail::mml
#elif defined(GLFW_BACKEND)
#include "impl/glfw/event.hpp"
#define impl detail::glfw
#else
#error "unsupported backend"
#endif

namespace os
{
namespace
{

std::deque<event>& get_event_queue()
{
	static std::deque<event> event_queue;
	return event_queue;
}

bool pop_event(event& e)
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

bool poll_event(event& e) noexcept
{
	impl::pump_events();

	return pop_event(e);
}

void push_event(const event& e)
{
	get_event_queue().push_back(e);
}
}
