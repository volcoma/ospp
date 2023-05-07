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
                    result.w = static_cast<uint32_t>(mode.screen_w);
                    result.h = static_cast<uint32_t>(mode.screen_h);
                    result.refresh_rate = static_cast<uint32_t>(mode.refresh_rate);
                    result.bpp = SDL_BITSPERPIXEL(mode.format);
                    return result;
                }
            }

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
                int count = 0;
                auto displays = SDL_GetDisplays(&index);
                std::vector<::os::display::mode> result;
                if(count < 1)
                {
                    SDL_free(displays);
                    OS_SDL_ERROR_HANDLER(result);
                }

                for(int i = 0; i < count; ++i)
                {
                    auto display_id = displays[i];
                    auto mode = SDL_GetDesktopDisplayMode(display_id);
                    if(!mode)
                    {
                        OS_SDL_ERROR_HANDLER(result);
                    }
                    result.push_back(from_impl(*mode));
                }
                SDL_free(displays);

                return result;
            }

            inline auto get_desktop_mode(int index = 0) -> ::os::display::mode
            {
                auto mode = SDL_GetDesktopDisplayMode(index);
                if(!mode)
                {
                    OS_SDL_ERROR_HANDLER({});
                }
                return from_impl(*mode);
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
