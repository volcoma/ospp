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
inline auto from_impl(const GLFWvidmode& mode) -> display_mode
{
	display_mode result;
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

inline auto get_available_modes(int index = 0) -> std::vector<display_mode>
{
	int mointor_count{0};
	auto monitors = glfwGetMonitors(&mointor_count);
	auto monitor = monitors[index];
	int count{0};
	auto modes = glfwGetVideoModes(monitor, &count);
	std::vector<display_mode> result;
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

inline auto get_desktop_mode(int index = 0) -> display_mode
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
}
}
}
