#include "keyboard.h"

#if defined(SDL_BACKEND)
#include "impl/sdl/keyboard.hpp"
#define impl detail::sdl
#elif defined(MML_BACKEND)
#include "impl/mml/keyboard.hpp"
#define impl detail::mml
#elif defined(GLFW_BACKEND)
#include "impl/glfw/keyboard.hpp"
#define impl detail::glfw
#else
#error "unsupported backend"
#endif

namespace os
{
namespace key
{

os::key::code from_string(const std::string& str) noexcept
{
	return impl::key::from_string(str);
}

std::string to_string(os::key::code key_code) noexcept
{
	return impl::key::to_string(key_code);
}

bool is_pressed(os::key::code key_code) noexcept
{
	return impl::key::is_pressed(key_code);
}
}

bool has_screen_keyboard() noexcept
{
	return impl::has_screen_keyboard();
}

void start_text_input() noexcept
{
	impl::start_text_input();
}

void stop_text_input() noexcept
{
	impl::stop_text_input();
}

bool is_text_input_active() noexcept
{
	return impl::is_text_input_active();
}
}
