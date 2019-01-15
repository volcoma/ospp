#pragma once
#include "../../event.h"

#include "config.hpp"
#include <cstring>
#include <deque>

namespace os
{
namespace detail
{
namespace sdl
{

inline window_event_id to_window_event_id(uint8_t id)
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

inline mouse::button to_mouse_button(uint8_t id)
{
	switch(id)
	{
		case SDL_BUTTON_LEFT:
			return mouse::button::left;
		case SDL_BUTTON_RIGHT:
			return mouse::button::right;
		case SDL_BUTTON_MIDDLE:
			return mouse::button::middle;
		case SDL_BUTTON_X1:
			return mouse::button::x1;
		case SDL_BUTTON_X2:
			return mouse::button::x2;
		default:
			return mouse::button::none;
	}
}

//	key_down = SDL_KEYDOWN,
//	key_up = SDL_KEYUP,
//	text_editing = SDL_TEXTEDITING,

//	finger_down = SDL_FINGERDOWN,
//	finger_up = SDL_FINGERUP,
//	finger_motion = SDL_FINGERMOTION,

inline event to_event(const SDL_Event& e)
{
	event ev;
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
			//		case events::key_down:
			//			break;
			//		case events::key_up:
			//			break;
			//		case events::text_editing:
			//			break;
		case SDL_TEXTINPUT:
			ev.type = events::text_input;
			ev.window.window_id = e.text.windowID;
			ev.text.text_utf8 = e.text.text;
			break;
		case SDL_MOUSEBUTTONDOWN:
			ev.type = events::mouse_button;
			ev.button.window_id = e.button.windowID;
			ev.button.button = to_mouse_button(e.button.button);
			ev.button.state = mouse::button_state::pressed;
			ev.button.x = e.button.x;
			ev.button.y = e.button.y;
			break;
		case SDL_MOUSEBUTTONUP:
			ev.type = events::mouse_button;
			ev.button.window_id = e.button.windowID;
			ev.button.button = to_mouse_button(e.button.button);
			ev.button.state = mouse::button_state::released;
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
            //e.wheel.
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
		push_event(e);
	}
}
}
}
}
