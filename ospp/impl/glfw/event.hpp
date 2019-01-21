#pragma once
#include "../../event.h"

#include "keyboard.hpp"
#include "mouse.hpp"
#include "window.hpp"

#include <codecvt>
#include <cstring>
#include <deque>
#include <locale>

namespace os
{
namespace detail
{
namespace glfw
{

inline auto to_state(int id) -> state
{
	switch(id)
	{
		case GLFW_RELEASE:
			return state::released;
		case GLFW_PRESS:
			return state::pressed;

		default:
			return state::none;
	}
}

inline void set_callbacks(GLFWwindow* window)
{
	glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		event ev{};
		ev.type = events::window;
		ev.window.window_id = impl->get_id();
		ev.window.type = window_event_id::close;

		push_event(ev);
	});

	glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		auto& focused_win = get_focused_win();
		if(focused == GL_TRUE)
		{
			focused_win = impl;
		}
		else
		{
			// only if this was the focused one
			if(focused_win == impl)
			{
				focused_win = nullptr;
			}
		}

		event ev{};
		ev.type = events::window;
		ev.window.window_id = impl->get_id();
		ev.window.type = focused == GL_TRUE ? window_event_id::focus_gained : window_event_id::focus_lost;

		push_event(ev);
	});

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int w, int h) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		event ev{};
		ev.type = events::window;
		ev.window.window_id = impl->get_id();
		ev.window.type = window_event_id::resized;
		ev.window.data1 = static_cast<int32_t>(w);
		ev.window.data2 = static_cast<int32_t>(h);

		push_event(ev);
	});

	glfwSetWindowPosCallback(window, [](GLFWwindow* window, int x, int y) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		event ev{};
		ev.type = events::window;
		ev.window.window_id = impl->get_id();
		ev.window.type = window_event_id::moved;
		ev.window.data1 = static_cast<int32_t>(x);
		ev.window.data2 = static_cast<int32_t>(y);

		push_event(ev);
	});

	glfwSetWindowMaximizeCallback(window, [](GLFWwindow* window, int mode) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		event ev{};
		ev.type = events::window;
		ev.window.window_id = impl->get_id();
		ev.window.type = mode == GLFW_TRUE ? window_event_id::maximized : window_event_id::restored;

		push_event(ev);
	});

	glfwSetCursorEnterCallback(window, [](GLFWwindow* window, int mode) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		event ev{};
		ev.type = events::window;
		ev.window.window_id = impl->get_id();
		ev.window.type = mode == GLFW_TRUE ? window_event_id::enter : window_event_id::leave;

		push_event(ev);
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		event ev{};
		ev.type = events::mouse_motion;
		ev.motion.window_id = impl->get_id();
		ev.motion.x = static_cast<int32_t>(x);
		ev.motion.y = static_cast<int32_t>(y);

		push_event(ev);
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		point pos{};
		double x{};
		double y{};
		glfwGetCursorPos(impl->get_impl(), &x, &y);
		pos.x = static_cast<int32_t>(x);
		pos.y = static_cast<int32_t>(y);

		event ev{};
		ev.type = events::mouse_button;
		ev.button.window_id = impl->get_id();
		ev.button.button = mouse::detail::glfw::from_impl(button);
		ev.button.state_id = to_state(action);
		ev.button.x = pos.x;
		ev.button.y = pos.y;

		push_event(ev);
	});

	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffs, double yoffs) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		event ev{};
		ev.type = events::mouse_wheel;
		ev.wheel.window_id = impl->get_id();
		ev.wheel.x = xoffs;
		ev.wheel.y = yoffs;

		push_event(ev);
	});

	glfwSetCharModsCallback(window, [](GLFWwindow* window, unsigned int unicode_codepoint, int) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		event ev{};
		ev.type = events::text_input;
		ev.text.window_id = impl->get_id();
		ev.text.text_utf8 =
			std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>{}.to_bytes(unicode_codepoint);

		push_event(ev);

	});
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		(void)scancode;
		event ev{};
		ev.type = action == GLFW_RELEASE ? events::key_up : events::key_down;
		ev.key.window_id = impl->get_id();
		ev.key.code = detail::glfw::from_layout_independent_impl(key);
		ev.key.alt = mods & GLFW_MOD_ALT;
		ev.key.ctrl = mods & GLFW_MOD_CONTROL;
		ev.key.shift = mods & GLFW_MOD_SHIFT;
		ev.key.system = mods & GLFW_MOD_SUPER;
		push_event(ev);

	});

	glfwSetDropCallback(window, [](GLFWwindow* window, int count, const char** paths) {
		auto user_data = glfwGetWindowUserPointer(window);
		auto impl = reinterpret_cast<window_impl*>(user_data);

		event ev{};
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
	auto all_closed = std::all_of(std::begin(windows), std::end(windows),
								  [](const auto& e) { return glfwWindowShouldClose(e->get_impl()); });
	if(all_closed)
	{
		event ev{};
		ev.type = events::quit;
		push_event(ev);
	}
}
}
}
}
