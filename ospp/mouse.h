#pragma once
#include "types.hpp"
#include "window.h"

namespace os
{
namespace mouse
{
enum class button : uint8_t
{
	none,
	left,
	middle,
	right,
	x1,
	x2,
	button_count ///< Keep last -- the total number of mouse buttons
};

auto is_button_pressed(button b) noexcept -> bool;

auto get_position() noexcept -> point;
auto get_position(const window& relative_to) noexcept -> point;

void set_position(const point& pos) noexcept;
void set_position(const point& pos, const window& relative_to) noexcept;

} // mouse
}
