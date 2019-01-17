#pragma once
#include "../../mouse.h"
#include "window.hpp"

namespace os
{
namespace mouse
{
namespace detail
{
namespace mml
{

inline button from_impl(::mml::mouse::button id)
{
	switch(id)
	{
		case ::mml::mouse::button::left:
			return button::left;
		case ::mml::mouse::button::right:
			return button::right;
		case ::mml::mouse::button::middle:
			return button::middle;
		case ::mml::mouse::button::x_button1:
			return button::x1;
		case ::mml::mouse::button::x_button2:
			return button::x2;
		default:
			return button::none;
	}
}

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
inline point get_position(const os::detail::mml::window_impl& win) noexcept
{
    auto pos = ::mml::mouse::get_position(win.get_impl());
    point result;
	result.x = pos[0];
	result.y = pos[1];
	return result;
}

inline void set_position(const point& pos) noexcept
{
	::mml::mouse::set_position({{pos.x, pos.y}});
}

inline void set_position(const point& pos, const os::detail::mml::window_impl& win) noexcept
{
	::mml::mouse::set_position({{pos.x, pos.y}}, win.get_impl());
}
}
}
}
}
