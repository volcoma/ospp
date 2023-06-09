#pragma once

#include <string>
#include <map>

namespace os
{
namespace detail
{
namespace glfw
{

#define HINT_MOUSE_FOCUS_CLICKTHROUGH "HINT_MOUSE_FOCUS_CLICKTHROUGH"
#define HINT_MOUSE_AUTO_CAPTURE "HINT_MOUSE_AUTO_CAPTURE"
#define HINT_BORDERLESS_WINDOWED_STYLE "HINT_BORDERLESS_WINDOWED_STYLE"

auto get_hints() -> std::map<std::string, std::string>&;

void set_hint(const std::string& hint, const std::string& value);
auto get_hint(const std::string& hint) -> const std::string&;
auto get_hint_value(const std::string& hint) -> int;

} // namespace glfw
} // namespace detail
} // namespace os
