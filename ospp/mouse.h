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

bool is_button_pressed(button b) noexcept;

point get_position() noexcept;
point get_position(const window& win) noexcept;

void set_position(const point& pos) noexcept;
void set_position(const point& pos, const window& win) noexcept;

} // mouse
}
