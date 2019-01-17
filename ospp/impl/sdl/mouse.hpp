#pragma once
#include "../../mouse.h"
#include "config.hpp"

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
inline void set_position(const point& pos) noexcept
{
	SDL_WarpMouseGlobal(pos.x, pos.y);
}
}
}
}
}
