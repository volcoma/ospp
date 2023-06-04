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

    glfwSetMonitorCallback([](GLFWmonitor* monitor, int e)
    {
        if(e == GLFW_DISCONNECTED)
        {
            event ev{};
            ev.type = events::display_disconnected;
            push_event(std::move(ev));
        }
        else if(e == GLFW_CONNECTED)
        {
            event ev{};
            ev.type = events::display_connected;
            push_event(std::move(ev));
        }
    });

	on_win_create() = set_callbacks;

    return true;
}

inline auto get_current_backend() -> const char*
{
    return "GLFW";
}
}
}
}
