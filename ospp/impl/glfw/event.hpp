#pragma once
#include "../../event.h"

#include <cstring>
#include <deque>

#include "window.hpp"

namespace os
{
namespace detail
{
namespace glfw
{

// inline window_event_id to_window_event_id(uint8_t id)
//{
//	switch(id)
//	{
//		case SDL_WINDOWEVENT_SHOWN:
//			return window_event_id::shown;
//		case SDL_WINDOWEVENT_HIDDEN:
//			return window_event_id::hidden;
//		case SDL_WINDOWEVENT_EXPOSED:
//			return window_event_id::exposed;
//		case SDL_WINDOWEVENT_MOVED:
//			return window_event_id::moved;
//		case SDL_WINDOWEVENT_RESIZED:
//			return window_event_id::resized;
//		case SDL_WINDOWEVENT_SIZE_CHANGED:
//			return window_event_id::size_changed;
//		case SDL_WINDOWEVENT_MAXIMIZED:
//			return window_event_id::maximized;
//		case SDL_WINDOWEVENT_MINIMIZED:
//			return window_event_id::minimized;
//		case SDL_WINDOWEVENT_RESTORED:
//			return window_event_id::restored;
//		case SDL_WINDOWEVENT_ENTER:
//			return window_event_id::enter;
//		case SDL_WINDOWEVENT_LEAVE:
//			return window_event_id::leave;
//		case SDL_WINDOWEVENT_FOCUS_GAINED:
//			return window_event_id::focus_gained;
//		case SDL_WINDOWEVENT_FOCUS_LOST:
//			return window_event_id::focus_lost;
//		case SDL_WINDOWEVENT_CLOSE:
//			return window_event_id::close;
//	}

//	return window_event_id::none;
//}

inline mouse::button to_mouse_button(int id)
{
	switch(id)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
			return mouse::button::left;
		case GLFW_MOUSE_BUTTON_RIGHT:
			return mouse::button::right;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			return mouse::button::middle;
		default:
			return mouse::button::none;
	}
}
inline mouse::button_state to_mouse_button_state(int id)
{
	switch(id)
	{
		case GLFW_RELEASE:
			return mouse::button_state::released;
		case GLFW_PRESS:
			return mouse::button_state::pressed;

		default:
			return mouse::button_state::none;
	}
}
////	key_down = SDL_KEYDOWN,
////	key_up = SDL_KEYUP,
////	text_editing = SDL_TEXTEDITING,

////	finger_down = SDL_FINGERDOWN,
////	finger_up = SDL_FINGERUP,
////	finger_motion = SDL_FINGERMOTION,

// inline event to_event(const SDL_Event& e)
//{
//	event ev;
//	switch(e.type)
//	{
//		case SDL_QUIT:
//			ev.type = events::quit;
//			break;
//		case SDL_APP_TERMINATING:
//			ev.type = events::app_terminating;
//			break;
//		case SDL_APP_LOWMEMORY:
//			ev.type = events::app_low_memory;
//			break;
//		case SDL_APP_WILLENTERBACKGROUND:
//			ev.type = events::app_will_enter_background;
//			break;
//		case SDL_APP_DIDENTERBACKGROUND:
//			ev.type = events::app_did_enter_background;
//			break;
//		case SDL_APP_WILLENTERFOREGROUND:
//			ev.type = events::app_will_enter_foreground;
//			break;
//		case SDL_APP_DIDENTERFOREGROUND:
//			ev.type = events::app_did_enter_foreground;
//			break;
//		case SDL_WINDOWEVENT:
//			ev.type = events::window;
//			ev.window.window_id = e.window.windowID;
//			ev.window.type = to_window_event_id(e.window.event);
//			ev.window.data1 = e.window.data1;
//			ev.window.data2 = e.window.data2;
//			break;
//			//		case events::key_down:
//			//			break;
//			//		case events::key_up:
//			//			break;
//			//		case events::text_editing:
//			//			break;
//		case SDL_TEXTINPUT:
//			ev.type = events::text_input;
//			ev.window.window_id = e.text.windowID;
//			ev.text.text_utf8 = e.text.text;
//			break;
//		case SDL_MOUSEBUTTONDOWN:
//			ev.type = events::mouse_button;
//			ev.button.window_id = e.button.windowID;
//			ev.button.button = to_mouse_button(e.button.button);
//			ev.button.state = mouse::button_state::pressed;
//			ev.button.x = e.button.x;
//			ev.button.y = e.button.y;
//			break;
//		case SDL_MOUSEBUTTONUP:
//			ev.type = events::mouse_button;
//			ev.button.window_id = e.button.windowID;
//			ev.button.button = to_mouse_button(e.button.button);
//			ev.button.state = mouse::button_state::released;
//			ev.button.x = e.button.x;
//			ev.button.y = e.button.y;
//			break;
//		case SDL_MOUSEMOTION:
//			ev.type = events::mouse_motion;
//			ev.motion.window_id = e.motion.windowID;
//			ev.motion.x = e.motion.x;
//			ev.motion.y = e.motion.y;
//			break;
//		case SDL_MOUSEWHEEL:
//			ev.type = events::mouse_wheel;
//			break;

//		case SDL_FINGERDOWN:
//			ev.type = events::finger_down;
//			break;
//		case SDL_FINGERUP:
//			ev.type = events::finger_up;

//			break;
//		case SDL_FINGERMOTION:
//			ev.type = events::finger_motion;
//			break;
//		case SDL_CLIPBOARDUPDATE:
//			ev.type = events::clipboard_update;
//			break;
//		case SDL_DROPFILE:
//			ev.type = events::drop_file;
//			ev.drop.window_id = e.drop.windowID;
//			if(e.drop.file != nullptr)
//			{
//				ev.drop.file = e.drop.file;
//				SDL_free(e.drop.file);
//			}
//			break;
//		default:
//			ev.type = events::unkwnown;
//	}

//	return ev;
//}
inline void set_callbacks(GLFWwindow* window)
{
	glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);
		impl->set_recieved_close_event(true);

		event ev;
		ev.type = events::window;
		ev.window.window_id = impl->get_id();
		ev.window.type = window_event_id::close;

		push_event(ev);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		event ev;
		ev.type = events::mouse_motion;
		ev.motion.window_id = impl->get_id();
		ev.motion.x = static_cast<int32_t>(x);
		ev.motion.y = static_cast<int32_t>(y);

		push_event(ev);
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);
        auto pos = impl->get_mouse_position();

		event ev;
		ev.type = events::mouse_button;
		ev.button.window_id = impl->get_id();
		ev.button.button = to_mouse_button(button);
		ev.button.state = to_mouse_button_state(action);
        ev.button.x = pos.x;
        ev.button.y = pos.y;

		push_event(ev);
	});

	glfwSetDropCallback(window, [](GLFWwindow* window, int count, const char** paths) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		event ev;
		ev.type = events::drop_file;
		ev.drop.window_id = impl->get_id();

		for(int i = 0; i < count; ++i)
		{
			ev.drop.file = paths[i];

			push_event(ev);
		}
	});
}

inline void pump_events() noexcept
{
	glfwPollEvents();

	auto& windows = get_windows();
	auto all_closed =
		std::all_of(std::begin(windows), std::end(windows), [](const auto& e) { return e->recieved_close_event(); });
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
