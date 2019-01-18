#pragma once
#include "../../mouse.h"
#include "window.hpp"

namespace os
{
namespace mouse
{
namespace detail
{
namespace sdl
{

inline button from_impl(uint8_t id)
{
	switch(id)
	{
		case SDL_BUTTON_LEFT:
			return button::left;
		case SDL_BUTTON_RIGHT:
			return button::right;
		case SDL_BUTTON_MIDDLE:
			return button::middle;
		case SDL_BUTTON_X1:
			return button::x1;
		case SDL_BUTTON_X2:
			return button::x2;
		default:
			return button::none;
	}
}

inline uint8_t to_impl(button b)
{
	switch(b)
	{
		case button::left:
			return SDL_BUTTON_LEFT;
		case button::right:
			return SDL_BUTTON_RIGHT;
		case button::middle:
			return SDL_BUTTON_MIDDLE;
		case button::x1:
			return SDL_BUTTON_X1;
		case button::x2:
			return SDL_BUTTON_X2;
		default:
			return SDL_BUTTON_LEFT;
	}
}

inline bool is_button_pressed(button b) noexcept
{
	auto impl_button = to_impl(b);
	return (SDL_GetGlobalMouseState(nullptr, nullptr) & SDL_BUTTON(impl_button)) != 0;
}

inline point get_position() noexcept
{
	point result;
	SDL_GetGlobalMouseState(&result.x, &result.y);
	return result;
}

inline point get_position(const os::detail::sdl::window_impl& win) noexcept
{
	SDL_PumpEvents();
	point relative_point;
	auto global_point = get_position();
	auto window_pos = win.get_position();
	relative_point.x = global_point.x - window_pos.x;
	relative_point.y = global_point.y - window_pos.y;
	return relative_point;
}

inline void set_position(const point& pos) noexcept
{
	SDL_WarpMouseGlobal(pos.x, pos.y);
}

inline void set_position(const point& pos, const os::detail::sdl::window_impl& win) noexcept
{
	SDL_WarpMouseInWindow(win.get_impl(), pos.x, pos.y);
}
}
}
}
}
