#include "hints.hpp"
#include "error.hpp"

namespace os
{
namespace detail
{
namespace glfw
{

auto get_hints() -> std::map<std::string, std::string>&
{
	static std::map<std::string, std::string> hints;
	return hints;
}

void set_hint(const std::string& hint, const std::string& value)
{
	get_hints()[hint] = value;
}

auto get_hint(const std::string& hint) -> const std::string&
{
	const auto& hints = get_hints();
	auto itr = hints.find(hint);
	if(itr != std::end(hints))
	{
		return itr->second;
	}

	static const std::string empty;
	return empty;
}

auto get_hint_value(const std::string& hint) -> int
{
	const auto& hint_value = get_hint(hint);
	if(hint == "1")
	{
		return GLFW_TRUE;
	}

	return GLFW_FALSE;
}

} // namespace glfw
} // namespace detail
} // namespace os
