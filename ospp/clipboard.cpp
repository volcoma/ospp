#include "clipboard.h"

#if defined(SDL_BACKEND)
#include "impl/sdl/clipboard.hpp"
#define impl detail::sdl
#elif defined(GLFW_BACKEND)
#include "impl/glfw/clipboard.hpp"
#define impl detail::glfw
#elif defined(MML_BACKEND)
#include "impl/mml/clipboard.hpp"
#define impl detail::mml
#else
#error "unsupported backend"
#endif

namespace os
{
namespace clipboard
{

std::string get_text() noexcept
{
    return impl::get_text();
}

void set_text(const std::string& text)
{
    impl::set_text(text);
}
}
}
