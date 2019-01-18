#pragma once

#include "../../keyboard.h"

#include "config.hpp"

namespace os
{
namespace clipboard
{

namespace detail
{
namespace sdl
{
inline std::string get_text() noexcept
{
	auto text = SDL_GetClipboardText();
	if(text)
	{
		std::string result = text;
		// must free according to docs
		SDL_free(text);
		return result;
	}
	return {};
}
inline void set_text(const std::string& text)
{
	SDL_SetClipboardText(text.c_str());
}
}
}
}
}
