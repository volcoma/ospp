#pragma once
#include "types.hpp"

namespace os
{
namespace mouse
{
enum class button
{
	none,
	left,
	middle,
	right,
	x1,
	x2,
	button_count ///< Keep last -- the total number of mouse buttons
};

enum class button_state
{
	none,
	pressed,
	released
};

bool is_button_pressed(button b) noexcept;

point get_position() noexcept;
} // mouse
}
