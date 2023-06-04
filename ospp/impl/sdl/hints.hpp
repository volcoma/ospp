#pragma once

#include "error.hpp"
#include <cstring>


namespace os
{
namespace detail
{
namespace sdl
{
inline void set_hint(const std::string& hint, const std::string& value)
{
    SDL_SetHint(hint.c_str(), value.c_str());
}
} // namespace sdl
} // namespace detail
} // namespace os
