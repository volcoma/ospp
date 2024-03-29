#pragma once

#include "../../cursor.h"

#include "error.hpp"

#include <algorithm>
#include <cstdint>
#include <cstring>
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
		SDL_DestroyCursor(cursor);
	}
};

class cursor_impl
{

public:
	cursor_impl(cursor::type system_type)
		: impl_(SDL_CreateSystemCursor(to_impl(system_type)))
	{
	}

	cursor_impl(const image& img, const point& hotspot)
	{
		auto surface =
			SDL_CreateSurfaceFrom((void*)img.pixels.data(), int(img.size.w), int(img.size.h),
								  int(img.size.w * 4), SDL_PixelFormatEnum::SDL_PIXELFORMAT_RGBA8888);
		if(!surface)
		{
			OS_SDL_ERROR_HANDLER_VOID();
		}

		impl_.reset(SDL_CreateColorCursor(surface, hotspot.x, hotspot.y));

		SDL_DestroySurface(surface);
	}

	auto get_impl() const noexcept -> SDL_Cursor*
	{
		return impl_.get();
	}

private:
	std::unique_ptr<SDL_Cursor, cursor_deleter> impl_;
};
} // namespace sdl
} // namespace detail
} // namespace os
