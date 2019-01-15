#include "display_mode.h"

#if defined(SDL_BACKEND)
#include "impl/sdl/display_mode.hpp"
#define impl detail::sdl
#elif defined(GLFW_BACKEND)
#include "impl/glfw/display_mode.hpp"
#define impl detail::glfw
#elif defined(MML_BACKEND)
#include "impl/mml/display_mode.hpp"
#define impl detail::mml
#else
#error "unsupported backend"
#endif

namespace os
{

auto number_of_video_displays() -> int
{
	return impl::number_of_video_displays();
}

auto display_mode::get_available_modes(int index) -> std::vector<display_mode>
{
	return impl::get_available_modes(index);
}

auto display_mode::get_desktop_mode(int index) -> display_mode
{
	return impl::get_desktop_mode(index);
}

auto display_mode::get_closest_mode(uint32_t width, uint32_t height, int index) -> display_mode
{
	display_mode to;
	to.w = width;
	to.h = height;
	return get_closest_mode(to, index);
}

auto display_mode::get_closest_mode(const display_mode& to, int index) -> display_mode
{
	auto desktop_mode = get_desktop_mode(index);
	auto modes = get_available_modes(index);

	uint32_t target_bpp{};
	if(to.bpp)
	{
		target_bpp = to.bpp;
	}
	else
	{
		target_bpp = desktop_mode.bpp;
	}

	uint32_t target_refresh_rate{};
	if(to.refresh_rate)
	{
		target_refresh_rate = to.refresh_rate;
	}
	else
	{
		target_refresh_rate = desktop_mode.refresh_rate;
	}

	const display_mode* match = nullptr;

	for(const auto& current : modes)
	{
		if(current.w && (current.w < to.w))
		{
			/* Out of sorted modes large enough here */
			break;
		}
		if(current.h && (current.h < to.h))
		{
			if(current.w && (current.w == to.w))
			{
				/* Out of sorted modes large enough here */
				break;
			}
			/* Wider, but not tall enough, due to a different
			   aspect ratio. This mode must be skipped, but closer
			   modes may still follow. */
			continue;
		}
		if(!match || current.w < match->w || current.h < match->h)
		{
			match = &current;
			continue;
		}
		if(current.bpp != match->bpp)
		{
			/* Sorted highest depth to lowest */
			if(current.bpp >= target_bpp)
			{
				match = &current;
			}
			continue;
		}
		if(current.refresh_rate != match->refresh_rate)
		{
			/* Sorted highest refresh to lowest */
			if(current.refresh_rate >= target_refresh_rate)
			{
				match = &current;
			}
		}
	}

	display_mode closest{};
	if(match)
	{
		if(match->bpp)
		{
			closest.bpp = match->bpp;
		}
		else
		{
			closest.bpp = to.bpp;
		}
		if(match->w && match->h)
		{
			closest.w = match->w;
			closest.h = match->h;
		}
		else
		{
			closest.w = to.w;
			closest.h = to.h;
		}
		if(match->refresh_rate)
		{
			closest.refresh_rate = match->refresh_rate;
		}
		else
		{
			closest.refresh_rate = to.refresh_rate;
		}

		/*
		 * Pick some reasonable defaults if the app and driver don't
		 * care
		 */
		if(!closest.bpp)
		{
			closest.bpp = 24;
		}
		if(!closest.w)
		{
			closest.w = 640;
		}
		if(!closest.h)
		{
			closest.h = 480;
		}
	}
	return closest;
}
}
