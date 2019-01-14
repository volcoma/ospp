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
	return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(impl_button)) != 0;
}

inline point get_position() noexcept
{
	point result;
	SDL_GetMouseState(&result.x, &result.y);
	return result;
}
}
}
}
}
