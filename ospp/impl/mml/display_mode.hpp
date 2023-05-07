#pragma once

#include "../../display_mode.h"

#include "error.hpp"
#include <vector>

namespace os
{
namespace detail
{
namespace mml
{
namespace
{
inline auto from_impl(const ::mml::video_mode& mode) -> ::os::display::mode
{
    ::os::display::mode result;
    result.w = mode.width;
    result.h = mode.height;
    result.bpp = mode.bits_per_pixel;
    result.refresh_rate = mode.refresh_rate;
	return result;
}

inline auto from_impl(const ::mml::video_bounds& bounds) -> ::os::display::bounds
{
    return {bounds.x, bounds.y, bounds.width, bounds.height};
}
}

inline int number_of_video_displays()
{
    return ::mml::get_number_of_displays();
}

inline auto get_available_modes(int index = 0) -> std::vector<::os::display::mode>
{
    auto modes = ::mml::video_mode::get_desktop_modes(index);
	std::vector<::os::display::mode> result;
	result.reserve(modes.size());
	for(const auto& mode : modes)
	{
		result.emplace_back(from_impl(mode));
	}

	return result;
}

inline auto get_desktop_mode(int index = 0) -> ::os::display::mode
{
    auto mode = ::mml::video_mode::get_desktop_mode(index);
    return from_impl(mode);
}

inline auto get_display_bounds(int index = 0) -> ::os::display::bounds
{
    auto bounds = ::mml::video_bounds::get_display_bounds(index);
    return from_impl(bounds);
}
}
}
}
