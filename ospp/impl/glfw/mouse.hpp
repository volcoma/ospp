#pragma once
#include "../../mouse.h"
#include "window.hpp"

namespace os
{
namespace mouse
{
namespace detail
{
namespace glfw
{

inline button from_impl(int id)
{
	switch(id)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
			return button::left;
		case GLFW_MOUSE_BUTTON_RIGHT:
			return button::right;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			return button::middle;
		case GLFW_MOUSE_BUTTON_4:
			return button::x1;
		case GLFW_MOUSE_BUTTON_5:
			return button::x2;
		default:
			return button::none;
	}
}
inline int to_impl(button b)
{
	switch(b)
	{
		case button::left:
			return GLFW_MOUSE_BUTTON_LEFT;
		case button::right:
			return GLFW_MOUSE_BUTTON_RIGHT;
		case button::middle:
			return GLFW_MOUSE_BUTTON_MIDDLE;
		case button::x1:
			return GLFW_MOUSE_BUTTON_4;
		case button::x2:
			return GLFW_MOUSE_BUTTON_5;
		default:
			return GLFW_MOUSE_BUTTON_LAST;
	}
}

inline bool is_button_pressed(button b) noexcept
{
	auto impl_button = to_impl(b);

	auto& focused_win = os::detail::glfw::get_focused_win();
	if(focused_win)
	{
		return glfwGetKey(focused_win->get_impl(), impl_button) != GLFW_RELEASE;
	}
	return false;
}

inline point get_position(const os::detail::glfw::window_impl& win) noexcept
{
	point result{};
	double x{};
	double y{};
	glfwGetCursorPos(win.get_impl(), &x, &y);
	result.x = static_cast<int32_t>(x);
	result.y = static_cast<int32_t>(y);
	return result;
}

inline point get_position() noexcept
{
	auto& focused_win = os::detail::glfw::get_focused_win();
	if(focused_win)
	{
		return get_position(*focused_win);
	}
	return {};
}

inline void set_position(const point& pos, const os::detail::glfw::window_impl& win) noexcept
{
	glfwSetCursorPos(win.get_impl(), static_cast<double>(pos.x), static_cast<double>(pos.y));
}
inline void set_position(const point& pos) noexcept
{
	auto& focused_win = os::detail::glfw::get_focused_win();
	if(focused_win)
	{
		set_position(pos, *focused_win);
	}
}
}
}
}
}
