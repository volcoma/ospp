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
		default:
			return button::none;
	}
}
// inline uint8_t to_impl(button b)
//{
//	switch(b)
//	{
//		case button::left:
//			return SDL_BUTTON_LEFT;
//		case button::right:
//			return SDL_BUTTON_RIGHT;
//		case button::middle:
//			return SDL_BUTTON_MIDDLE;
//		case button::x1:
//			return SDL_BUTTON_X1;
//		case button::x2:
//			return SDL_BUTTON_X2;
//		default:
//			return SDL_BUTTON_LEFT;
//	}
//}

inline bool is_button_pressed(button b) noexcept
{
	return false;
}

inline point get_position() noexcept
{
	return {};
}

inline point get_position(const os::detail::glfw::window_impl& win) noexcept
{
	return {};
}

inline void set_position(const point& pos) noexcept
{
}

inline void set_position(const point& pos, const os::detail::glfw::window_impl& win) noexcept
{
    //glfwSetCursorPos(impl_.get(), static_cast<double>(pos.x), static_cast<double>(pos.y));
}

}
}
}
}
