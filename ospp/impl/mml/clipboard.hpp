#pragma once

#include "../../keyboard.h"

#include "config.hpp"

namespace os
{
namespace clipboard
{

namespace detail
{
namespace mml
{
inline std::string get_text() noexcept
{
	return ::mml::clipboard::get_string();
}
inline void set_text(const std::string& text)
{
	::mml::clipboard::set_string(text);
}
}
}
}
}
