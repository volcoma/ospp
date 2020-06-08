#pragma once
#include "../../mouse.h"
#include "window.hpp"

namespace os
{
    namespace mouse
    {
        namespace detail
        {
            namespace sdl
            {
                using window_impl = os::detail::sdl::window_impl;
                inline auto to_win_impl(const window& win) -> const window_impl&
                {
                    return *reinterpret_cast<window_impl*>(win.get_impl());
                }

                inline auto from_impl(uint8_t id) -> button
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

                inline auto to_impl(button b) -> uint8_t
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

                inline auto is_button_pressed(button b) noexcept -> bool
                {
                    auto impl_button = to_impl(b);
                    return (SDL_GetGlobalMouseState(nullptr, nullptr) & SDL_BUTTON(impl_button)) != 0;
                }

                inline auto get_position() noexcept -> point
                {
                    point result{};
                    SDL_GetGlobalMouseState(&result.x, &result.y);
                    return result;
                }

                inline point get_position(const window& relative_to) noexcept
                {
                    point relative_pos{};
                    auto global_pos = get_position();
                    auto window_pos = to_win_impl(relative_to).get_position();
                    relative_pos.x = global_pos.x - window_pos.x;
                    relative_pos.y = global_pos.y - window_pos.y;
                    return relative_pos;
                }

                inline void set_position(const point& pos) noexcept
                {
                    SDL_WarpMouseGlobal(pos.x, pos.y);
                }

                inline void set_position(const point& pos, const window& relative_to) noexcept
                {
                    SDL_WarpMouseInWindow(to_win_impl(relative_to).get_impl(), pos.x, pos.y);
                }
            }
        }
    }
}
