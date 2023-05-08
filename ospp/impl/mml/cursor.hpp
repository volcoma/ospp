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
namespace mml
{
inline auto to_impl(cursor::type system_type) -> ::mml::cursor::type
{
	switch(system_type)
	{
		case cursor::arrow:
			return ::mml::cursor::arrow;
		case cursor::arrow_wait:
			return ::mml::cursor::arrow_wait;
		case cursor::crosshair:
			return ::mml::cursor::cross;
		case cursor::hand:
			return ::mml::cursor::hand;
		case cursor::ibeam:
			return ::mml::cursor::text;
		case cursor::not_allowed:
			return ::mml::cursor::not_allowed;
		case cursor::size_all:
			return ::mml::cursor::size_all;
		case cursor::size_nesw:
			return ::mml::cursor::size_bottom_left_top_right;
		case cursor::size_ns:
			return ::mml::cursor::size_vertical;
		case cursor::size_nwse:
			return ::mml::cursor::size_top_left_bottom_right;
		case cursor::size_we:
			return ::mml::cursor::size_horizontal;
		default:
			return ::mml::cursor::arrow;
	}
}
class cursor_impl
{

public:
	cursor_impl(cursor::type system_type)
	{
		impl_.load_from_system(to_impl(system_type));
	}

	cursor_impl(const image& img, const point& hotspot)
	{
		impl_.load_from_pixels(img.pixels.data(), {{img.size.w, img.size.h}},
							   {{uint32_t(hotspot.x), uint32_t(hotspot.y)}});
	}

	auto get_impl() const noexcept -> const ::mml::cursor&
	{
		return impl_;
	}

private:
	::mml::cursor impl_;
};
} // namespace mml
} // namespace detail
} // namespace os
