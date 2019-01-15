#pragma once
#include "../../mouse.h"
#include "config.hpp"

namespace os
{
namespace mouse
{
namespace detail
{
namespace mml
{

inline ::mml::mouse::button to_impl(button b)
{
	switch(b)
	{
		case button::left:
			return ::mml::mouse::button::left;
		case button::right:
			return ::mml::mouse::button::right;
		case button::middle:
			return ::mml::mouse::button::middle;
		case button::x1:
			return ::mml::mouse::button::x_button1;
		case button::x2:
			return ::mml::mouse::button::x_button2;
		default:
			return ::mml::mouse::button::button_count;
	}
}

inline bool is_button_pressed(button b) noexcept
{
	auto impl_button = to_impl(b);
	return ::mml::mouse::is_button_pressed(impl_button);
}

inline point get_position() noexcept
{
	auto pos = ::mml::mouse::get_position();
	point result;
	result.x = pos[0];
	result.y = pos[1];
	return result;
}
}
}
}
}
