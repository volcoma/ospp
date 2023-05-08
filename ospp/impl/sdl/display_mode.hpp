#pragma once

#include "../../display_mode.h"

#include "error.hpp"
#include <vector>

namespace os
{b
namespace detail
{
namespace sdl
{
namespace
{
inline auto from_impl(const SDL_DisplayMode& mode) -> ::os::display::mode
{
	::os::display::mode result;
	result.w = static_cast<uint32_t>(mode.screen_w);
	result.h = static_cast<uint32_t>(mode.screen_h);
	result.refresh_rate = static_cast<uint32_t>(mode.refresh_rate);
	result.bpp = SDL_BITSPERPIXEL(mode.format);
    result.display_scale = mode.display_scale;
	return result;
}

inline auto to_display_id(int display_index) -> SDL_DisplayID
{
	int count = 0;
	auto displays = SDL_GetDisplays(&count);

	SDL_DisplayID display_id{};
	if(display_index < count)
	{
		display_id = displays[display_index];
	}

	SDL_free(displays);
	return display_id;
}

} // namespace

inline auto number_of_video_displays() -> int
{
	int result = 0;
	auto displays = SDL_GetDisplays(&result);
	if(result < 1)
	{
		SDL_free(displays);
		OS_SDL_ERROR_HANDLER(result);
	}
	SDL_free(displays);
	return result;
}

inline auto get_available_modes(int index = 0) -> std::vector<::os::display::mode>
{
    std::vector<::os::display::mode> result;

	auto display_id = to_display_id(index);

	int count{};
	auto modes = SDL_GetFullscreenDisplayModes(display_id, &count);
	for(int i = 0; i < count; ++i)
	{
		auto mode = modes[i];
		if(!mode)
		{
			SDL_free(modes);
			OS_SDL_ERROR_HANDLER(result);
		}
		result.push_back(from_impl(*mode));
	}
	SDL_free(modes);

	return result;
}

inline auto get_desktop_mode(int index = 0) -> ::os::display::mode
{
    auto display_id = to_display_id(index);
	auto mode = SDL_GetDesktopDisplayMode(display_id);
	if(!mode)
	{
		OS_SDL_ERROR_HANDLER({});
	}
	return from_impl(*mode);
}

inline auto get_display_bounds(int index = 0) -> ::os::display::bounds
{
    auto display_id = to_display_id(index);

	SDL_Rect rect{};
	if(SDL_GetDisplayBounds(display_id, &rect) == 0)
	{
		return {rect.x, rect.y, static_cast<uint32_t>(rect.w), static_cast<uint32_t>(rect.h)};
	}

	return {};
}
} // namespace sdl
} // namespace detail
} // namespace os
