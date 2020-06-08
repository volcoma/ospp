#pragma once

#include "../../display_mode.h"

#include "error.hpp"
#include <vector>

namespace os
{
namespace detail
{
namespace glfw
{
namespace
{
inline auto from_impl(const GLFWvidmode& mode) -> ::os::display::mode
{
    ::os::display::mode result;
	result.w = static_cast<uint32_t>(mode.width);
	result.h = static_cast<uint32_t>(mode.height);
	result.refresh_rate = static_cast<uint32_t>(mode.refreshRate);
	result.bpp = static_cast<uint32_t>(mode.redBits + mode.greenBits + mode.blueBits);
	return result;
}
}

inline auto number_of_video_displays() -> int
{
	int result{0};
	glfwGetMonitors(&result);
	if(result < 1)
	{
		OS_GLFW_ERROR_HANDLER(result);
	}
	return result;
}

inline auto get_available_modes(int index = 0) -> std::vector<::os::display::mode>
{
	int mointor_count{0};
	auto monitors = glfwGetMonitors(&mointor_count);
	auto monitor = monitors[index];
	int count{0};
	auto modes = glfwGetVideoModes(monitor, &count);
    std::vector<::os::display::mode> result;
	if(count < 1)
	{
		OS_GLFW_ERROR_HANDLER(result);
	}

	for(int i = 0; i < count; ++i)
	{
		auto mode = modes[i];
		result.push_back(from_impl(mode));
	}

	return result;
}

inline auto get_desktop_mode(int index = 0) -> ::os::display::mode
{
	int mointor_count{0};
	auto monitors = glfwGetMonitors(&mointor_count);
	auto monitor = monitors[index];
	auto result = glfwGetVideoMode(monitor);
	if(result)
	{
		return from_impl(*result);
	}

	return {};
}

inline auto get_display_bounds(int index = 0) -> ::os::display::bounds
{
    int mointor_count{0};
    auto monitors = glfwGetMonitors(&mointor_count);
    auto monitor = monitors[index];
    ::os::display::bounds result {};
    int width {};
    int height {};
    glfwGetMonitorWorkarea(monitor, &result.x, &result.y, &width, &height);
    result.w = uint32_t(width);
    result.h = uint32_t(height);

    return result;
}
}
}
}
