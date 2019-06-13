#pragma once
#include "error.hpp"
#include "event.hpp"

namespace os
{
namespace detail
{
namespace glfw
{
inline void shutdown() noexcept
{
	glfwTerminate();
}

inline auto init() -> int
{
	auto result = glfwInit();
	if(result == GLFW_FALSE)
	{
		OS_GLFW_ERROR_HANDLER(result);
        return false;
	}

	on_win_create() = set_callbacks;

    return true;
}
}
}
}
