#pragma once
#include "../../event.h"

#include "window.hpp"

#include "config.hpp"

#include <algorithm>
#include <codecvt>
#include <cstring>
#include <deque>
#include <locale>
namespace os
{
namespace detail
{
namespace mml
{

inline mouse::button to_mouse_button(::mml::mouse::button id)
{
	switch(id)
	{
		case ::mml::mouse::button::left:
			return mouse::button::left;
		case ::mml::mouse::button::right:
			return mouse::button::right;
		case ::mml::mouse::button::middle:
			return mouse::button::middle;
		case ::mml::mouse::button::x_button1:
			return mouse::button::x1;
		case ::mml::mouse::button::x_button2:
			return mouse::button::x2;
		default:
			return mouse::button::none;
	}
}

////	key_down = SDL_KEYDOWN,
////	key_up = SDL_KEYUP,
////	text_editing = SDL_TEXTEDITING,

////	finger_down = SDL_FINGERDOWN,
////	finger_up = SDL_FINGERUP,
////	finger_motion = SDL_FINGERMOTION,

inline event to_event(const ::mml::platform_event& e, uint32_t window_id)
{
	event ev;
	switch(e.type)
	{
		case ::mml::platform_event::closed:
			ev.type = events::window;
			ev.window.window_id = window_id;
			ev.window.type = window_event_id::close;
			break;
		case ::mml::platform_event::resized:
			ev.type = events::window;
			ev.window.window_id = window_id;
			ev.window.type = window_event_id::resized;
			ev.window.data1 = static_cast<int32_t>(e.size.width);
			ev.window.data2 = static_cast<int32_t>(e.size.height);
			break;
		case ::mml::platform_event::lost_focus:
			ev.type = events::window;
			ev.window.window_id = window_id;
			ev.window.type = window_event_id::focus_lost;
			break;
		case ::mml::platform_event::gained_focus:
			ev.type = events::window;
			ev.window.window_id = window_id;
			ev.window.type = window_event_id::focus_gained;
			break;
		case ::mml::platform_event::mouse_entered:
			ev.type = events::window;
			ev.window.window_id = window_id;
			ev.window.type = window_event_id::enter;
			break;
		case ::mml::platform_event::mouse_left:
			ev.type = events::window;
			ev.window.window_id = window_id;
			ev.window.type = window_event_id::leave;
			break;
		case ::mml::platform_event::key_pressed:
			ev.type = events::key_down;
			break;
		case ::mml::platform_event::key_released:
			ev.type = events::key_up;
			break;

		case ::mml::platform_event::text_entered:
			ev.type = events::text_input;
			ev.window.window_id = window_id;
			ev.text.text_utf8 =
				std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>{}.to_bytes(e.text.unicode);
			break;
		case ::mml::platform_event::mouse_button_pressed:
			ev.type = events::mouse_button;
			ev.button.window_id = window_id;
			ev.button.button = to_mouse_button(e.mouse_button.button);
			ev.button.state = mouse::button_state::pressed;
			ev.button.x = e.mouse_button.x;
			ev.button.y = e.mouse_button.y;
			break;
		case ::mml::platform_event::mouse_button_released:
			ev.type = events::mouse_button;
			ev.button.window_id = window_id;
			ev.button.button = to_mouse_button(e.mouse_button.button);
			ev.button.state = mouse::button_state::released;
			ev.button.x = e.mouse_button.x;
			ev.button.y = e.mouse_button.y;
			break;
		case ::mml::platform_event::mouse_moved:
			ev.type = events::mouse_motion;
			ev.motion.window_id = window_id;
			ev.motion.x = e.mouse_move.x;
			ev.motion.y = e.mouse_move.y;
			break;
		case ::mml::platform_event::mouse_wheel_scrolled:
			ev.type = events::mouse_wheel;
			// e.mouse_wheel_scroll
			break;

		case ::mml::platform_event::touch_began:
			ev.type = events::finger_down;
			break;
		case ::mml::platform_event::touch_ended:
			ev.type = events::finger_up;

			break;
		case ::mml::platform_event::touch_moved:
			ev.type = events::finger_motion;
			break;

		default:
			ev.type = events::unkwnown;
	}

	return ev;
}

inline void pump_events() noexcept
{
	auto& windows = get_windows();
	for(auto& window : windows)
	{
		auto& impl = window->get_impl();

		::mml::platform_event ev;
		if(impl.poll_event(ev))
		{
			if(ev.type == ::mml::platform_event::closed)
			{
				window->set_recieved_close_event(true);
			}
			auto e = to_event(ev, window->get_id());

			push_event(e);
		}
	}

	auto all_closed = std::all_of(std::begin(windows), std::end(windows),
								  [](const auto& e) { return e->recieved_close_event(); });
	if(all_closed)
	{
		event ev;
		ev.type = events::quit;
		push_event(ev);
	}
}
}
}
}
