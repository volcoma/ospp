#pragma once
#include "../../event.h"

#include "keyboard.hpp"
#include "mouse.hpp"

#include <cstring>
#include <deque>

namespace os
{
namespace detail
{
namespace sdl
{

inline auto to_window_event_id(uint8_t id) -> window_event_id
{
	switch(id)
	{
		case SDL_WINDOWEVENT_SHOWN:
			return window_event_id::shown;
		case SDL_WINDOWEVENT_HIDDEN:
			return window_event_id::hidden;
		case SDL_WINDOWEVENT_EXPOSED:
			return window_event_id::exposed;
		case SDL_WINDOWEVENT_MOVED:
			return window_event_id::moved;
		case SDL_WINDOWEVENT_RESIZED:
			return window_event_id::resized;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			return window_event_id::size_changed;
		case SDL_WINDOWEVENT_MAXIMIZED:
			return window_event_id::maximized;
		case SDL_WINDOWEVENT_MINIMIZED:
			return window_event_id::minimized;
		case SDL_WINDOWEVENT_RESTORED:
			return window_event_id::restored;
		case SDL_WINDOWEVENT_ENTER:
			return window_event_id::enter;
		case SDL_WINDOWEVENT_LEAVE:
			return window_event_id::leave;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			return window_event_id::focus_gained;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			return window_event_id::focus_lost;
		case SDL_WINDOWEVENT_CLOSE:
			return window_event_id::close;
	}

	return window_event_id::none;
}

inline auto to_event(const SDL_Event& e) -> event
{
	event ev{};
	switch(e.type)
	{
		case SDL_QUIT:
			ev.type = events::quit;
			break;
		case SDL_APP_TERMINATING:
			ev.type = events::app_terminating;
			break;
		case SDL_APP_LOWMEMORY:
			ev.type = events::app_low_memory;
			break;
		case SDL_APP_WILLENTERBACKGROUND:
			ev.type = events::app_will_enter_background;
			break;
		case SDL_APP_DIDENTERBACKGROUND:
			ev.type = events::app_did_enter_background;
			break;
		case SDL_APP_WILLENTERFOREGROUND:
			ev.type = events::app_will_enter_foreground;
			break;
		case SDL_APP_DIDENTERFOREGROUND:
			ev.type = events::app_did_enter_foreground;
			break;
		case SDL_WINDOWEVENT:
			ev.type = events::window;
			ev.window.window_id = e.window.windowID;
			ev.window.type = to_window_event_id(e.window.event);
			ev.window.data1 = e.window.data1;
			ev.window.data2 = e.window.data2;
			break;
		case SDL_KEYDOWN:
			ev.type = events::key_down;
			ev.key.window_id = e.key.windowID;
			ev.key.code = detail::sdl::from_layout_independent_impl(e.key.keysym.scancode);
			ev.key.alt = e.key.keysym.mod & KMOD_ALT;
			ev.key.ctrl = e.key.keysym.mod & KMOD_CTRL;
			ev.key.shift = e.key.keysym.mod & KMOD_SHIFT;
			ev.key.system = e.key.keysym.mod & KMOD_GUI;
			break;
		case SDL_KEYUP:
			ev.type = events::key_up;
			ev.key.window_id = e.key.windowID;
			ev.key.code = detail::sdl::from_layout_independent_impl(e.key.keysym.scancode);
			ev.key.alt = e.key.keysym.mod & KMOD_ALT;
			ev.key.ctrl = e.key.keysym.mod & KMOD_CTRL;
			ev.key.shift = e.key.keysym.mod & KMOD_SHIFT;
			ev.key.system = e.key.keysym.mod & KMOD_GUI;
			break;
		case SDL_TEXTINPUT:
			ev.type = events::text_input;
			ev.text.window_id = e.text.windowID;
			ev.text.text = e.text.text;
			break;
		case SDL_MOUSEBUTTONDOWN:
			ev.type = events::mouse_button;
			ev.button.window_id = e.button.windowID;
			ev.button.button = mouse::detail::sdl::from_impl(e.button.button);
			ev.button.state_id = state::pressed;
			ev.button.x = e.button.x;
			ev.button.y = e.button.y;
			break;
		case SDL_MOUSEBUTTONUP:
			ev.type = events::mouse_button;
			ev.button.window_id = e.button.windowID;
			ev.button.button = mouse::detail::sdl::from_impl(e.button.button);
			ev.button.state_id = state::released;
			ev.button.x = e.button.x;
			ev.button.y = e.button.y;
			break;
		case SDL_MOUSEMOTION:
			ev.type = events::mouse_motion;
			ev.motion.window_id = e.motion.windowID;
			ev.motion.x = e.motion.x;
			ev.motion.y = e.motion.y;
			break;
		case SDL_MOUSEWHEEL:
			ev.type = events::mouse_wheel;
			ev.wheel.window_id = e.wheel.windowID;
			ev.wheel.which = e.wheel.which;
			ev.wheel.x = static_cast<double>(e.wheel.x);
			ev.wheel.y = static_cast<double>(e.wheel.y);
			break;
		case SDL_FINGERDOWN:
			ev.type = events::finger_down;
			break;
		case SDL_FINGERUP:
			ev.type = events::finger_up;
			break;
		case SDL_FINGERMOTION:
			ev.type = events::finger_motion;
			break;
		case SDL_CLIPBOARDUPDATE:
			ev.type = events::clipboard_update;
			break;
		case SDL_DROPFILE:
			ev.type = events::drop_file;
			ev.drop.window_id = e.drop.windowID;
			if(e.drop.file != nullptr)
			{
				ev.drop.file = e.drop.file;
				SDL_free(e.drop.file);
			}
			break;
		default:
			ev.type = events::unkwnown;
	}

	return ev;
}

inline void pump_events() noexcept
{
	SDL_Event ev{};
	while(SDL_PollEvent(&ev) != 0)
	{
		auto e = to_event(ev);
		push_event(std::move(e));
	}
}
}
}
}
