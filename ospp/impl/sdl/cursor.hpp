#pragma once

#include "../../cursor.h"

#include "error.hpp"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>

namespace os
{
namespace detail
{
namespace sdl
{

inline auto to_impl(cursor::type system_type) -> SDL_SystemCursor
{
	switch(system_type)
	{
		case cursor::arrow:
			return SDL_SYSTEM_CURSOR_ARROW;
		case cursor::arrow_wait:
			return SDL_SYSTEM_CURSOR_WAITARROW;
		case cursor::crosshair:
			return SDL_SYSTEM_CURSOR_CROSSHAIR;
		case cursor::hand:
			return SDL_SYSTEM_CURSOR_HAND;
		case cursor::ibeam:
			return SDL_SYSTEM_CURSOR_IBEAM;
		case cursor::not_allowed:
			return SDL_SYSTEM_CURSOR_NO;
		case cursor::size_all:
			return SDL_SYSTEM_CURSOR_SIZEALL;
		case cursor::size_nesw:
			return SDL_SYSTEM_CURSOR_SIZENESW;
		case cursor::size_ns:
			return SDL_SYSTEM_CURSOR_SIZENS;
		case cursor::size_nwse:
			return SDL_SYSTEM_CURSOR_SIZENWSE;
		case cursor::size_we:
			return SDL_SYSTEM_CURSOR_SIZEWE;
		default:
			return SDL_SYSTEM_CURSOR_ARROW;
	}
}

struct cursor_deleter
{
	void operator()(SDL_Cursor* cursor) const noexcept
	{
		SDL_FreeCursor(cursor);
	}
};

class cursor_impl
{

public:
	cursor_impl(cursor::type system_type)
		: impl_(SDL_CreateSystemCursor(to_impl(system_type)))
	{
	}

	auto get_impl() const noexcept -> SDL_Cursor*
	{
		return impl_.get();
	}

private:
	std::unique_ptr<SDL_Cursor, cursor_deleter> impl_;
};
}
}
}
