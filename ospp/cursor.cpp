#include "cursor.h"

#if defined(SDL_BACKEND)
#include "impl/sdl/cursor.hpp"
using impl_type = os::detail::sdl::cursor_impl;
#elif defined(MML_BACKEND)
#include "impl/mml/cursor.hpp"
using impl_type = os::detail::mml::cursor_impl;
#elif defined(GLFW_BACKEND)
#include "impl/glfw/cursor.hpp"
using impl_type = os::detail::glfw::cursor_impl;
#else
#error "unsupported backend"
#endif

#define this_impl to_impl(impl_.get())

namespace os
{

inline auto to_impl(void* obj) -> impl_type*
{
	return reinterpret_cast<impl_type*>(obj);
}

cursor::cursor(cursor::type system_type)
	: impl_(std::make_shared<impl_type>(system_type))
{
}

cursor::cursor(const image& img, const point& hotspot)
	: impl_(std::make_shared<impl_type>(img, hotspot))
{
}

auto cursor::get_impl() const noexcept -> void*
{
	return impl_.get();
}
}
