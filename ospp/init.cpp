#include "init.h"

#if defined(SDL_BACKEND)
#include "impl/sdl/init.hpp"
#define impl detail::sdl
#elif defined(MML_BACKEND)
#include "impl/mml/init.hpp"
#define impl detail::mml
#elif defined(GLFW_BACKEND)
#include "impl/glfw/init.hpp"
#define impl detail::glfw
#else
#error "unsupported backend"
#endif

namespace os
{

void shutdown() noexcept
{
	impl::shutdown();
}

auto init() -> bool
{
	return impl::init();
}
}
