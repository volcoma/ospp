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
inline auto from_impl(const ::mml::video_mode& mode) -> display_mode
{
	display_mode result;
	result.w = static_cast<uint32_t>(mode.width);
	result.h = static_cast<uint32_t>(mode.height);
	result.bpp = static_cast<uint32_t>(mode.bits_per_pixel);
	result.refresh_rate = 0;
	return result;
}
}

inline int number_of_video_displays()
{
	return 1;
}

inline auto get_available_modes(int /*index = 0*/) -> std::vector<display_mode>
{
	auto modes = ::mml::video_mode::get_fullscreen_modes();
	std::vector<display_mode> result;
	result.reserve(modes.size());
	for(const auto& mode : modes)
	{
		result.emplace_back(from_impl(mode));
	}

	return result;
}

inline auto get_desktop_mode(int /*index = 0*/) -> display_mode
{
	auto mode = ::mml::video_mode::get_desktop_mode();
	return from_impl(mode);
}
}
}
}
