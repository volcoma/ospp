#include "mouse.h"

#if defined(SDL_BACKEND)
#include "impl/sdl/mouse.hpp"
#define impl detail::sdl
#elif defined(MML_BACKEND)
#include "impl/mml/mouse.hpp"
#define impl detail::mml
#elif defined(GLFW_BACKEND)
#include "impl/glfw/mouse.hpp"
#define impl detail::glfw
#else
#error "unsupported backend"
#endif

namespace os
{
namespace mouse
{

bool is_button_pressed(button b) noexcept
{
	return impl::is_button_pressed(b);
}

point get_position() noexcept
{
	return impl::get_position();
}

point get_position(const window& win) noexcept
{
	return impl::get_position();
}

void set_position(const point& pos) noexcept
{
	impl::set_position(pos);
}

void set_position(const point& pos, const window& win) noexcept
{
	impl::set_position(pos);
}
}
}
