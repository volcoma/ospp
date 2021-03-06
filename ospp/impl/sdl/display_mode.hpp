#pragma once

#include "../../display_mode.h"

#include "error.hpp"
#include <vector>

namespace os
{
    namespace detail
    {
        namespace sdl
        {
            namespace
            {
                inline auto from_impl(const SDL_DisplayMode& mode) -> ::os::display::mode
                {
                    ::os::display::mode result;
                    result.w = static_cast<uint32_t>(mode.w);
                    result.h = static_cast<uint32_t>(mode.h);
                    result.refresh_rate = static_cast<uint32_t>(mode.refresh_rate);
                    result.bpp = SDL_BITSPERPIXEL(mode.format);
                    return result;
                }
            }

            inline auto number_of_video_displays() -> int
            {
                int result = SDL_GetNumVideoDisplays();
                if(result < 1)
                {
                    OS_SDL_ERROR_HANDLER(result);
                }
                return result;
            }

            inline auto get_available_modes(int index = 0) -> std::vector<::os::display::mode>
            {
                int count = SDL_GetNumDisplayModes(index);
                std::vector<::os::display::mode> result;
                if(count < 1)
                {
                    OS_SDL_ERROR_HANDLER(result);
                }

                SDL_DisplayMode mode{};
                for(int i = 0; i < count; ++i)
                {
                    if(SDL_GetDisplayMode(index, i, &mode))
                    {
                        OS_SDL_ERROR_HANDLER(result);
                    }
                    result.push_back(from_impl(mode));
                }

                return result;
            }

            inline auto get_desktop_mode(int index = 0) -> ::os::display::mode
            {
                SDL_DisplayMode result{};
                if(SDL_GetDesktopDisplayMode(index, &result))
                {
                    OS_SDL_ERROR_HANDLER(from_impl(result));
                }
                return from_impl(result);
            }

            inline auto get_display_bounds(int index = 0) -> ::os::display::bounds
            {
                SDL_Rect rect{};
                if (SDL_GetDisplayBounds(index, &rect) == 0)
                {
                    return {rect.x, rect.y, static_cast<uint32_t>(rect.w), static_cast<uint32_t>(rect.h)};
                }

                return {};
            }
        }
    }
}
