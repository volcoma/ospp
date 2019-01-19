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
namespace glfw
{
inline auto to_impl(cursor::type system_type) -> int
{
	switch(system_type)
	{
		case cursor::arrow:
			return GLFW_ARROW_CURSOR;
		case cursor::crosshair:
			return GLFW_CROSSHAIR_CURSOR;
		case cursor::hand:
			return GLFW_HAND_CURSOR;
		case cursor::ibeam:
			return GLFW_IBEAM_CURSOR;
		case cursor::size_ns:
			return GLFW_VRESIZE_CURSOR;
		case cursor::size_we:
			return GLFW_HRESIZE_CURSOR;
		default:
			return GLFW_ARROW_CURSOR;
	}
}
struct cursor_deleter
{
	void operator()(GLFWcursor* cursor) const noexcept
	{
		glfwDestroyCursor(cursor);
	}
};

class cursor_impl
{

public:
	cursor_impl(cursor::type system_type)
		: impl_(glfwCreateStandardCursor(to_impl(system_type)))
	{
	}

	cursor_impl(const image& img, const point& hotspot)
	{
		GLFWimage image{};
		image.pixels = (unsigned char*)img.pixels.data();
		image.width = static_cast<int>(img.size.w);
		image.height = static_cast<int>(img.size.h);
		impl_.reset(glfwCreateCursor(&image, hotspot.x, hotspot.y));
	}

	auto get_impl() const noexcept -> GLFWcursor*
	{
		return impl_.get();
	}

private:
	std::unique_ptr<GLFWcursor, cursor_deleter> impl_;
};
}
}
}
