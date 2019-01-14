#pragma once
#include "error.hpp"

namespace os
{
namespace detail
{
namespace sdl
{
inline void shutdown() noexcept
{
	SDL_Quit();
}

inline auto init() -> int
{
	auto result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC |
						   SDL_INIT_GAMECONTROLLER | SDL_INIT_SENSOR);
	if(result < 0)
	{
		OS_SDL_ERROR_HANDLER(result);
	}

	return 0;
}
}
}

}
