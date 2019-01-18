#pragma once

#include "../../keyboard.h"

#include "config.hpp"

namespace os
{
namespace clipboard
{

namespace detail
{
namespace glfw
{
inline std::string get_text() noexcept
{
	auto text = glfwGetClipboardString(nullptr);
	if(text)
	{
		return text;
	}
	return {};
}
inline void set_text(const std::string& text)
{
	glfwSetClipboardString(nullptr, text.c_str());
}
}
}
}
}
