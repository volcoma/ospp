#include "../../keyboard.h"

#include "config.hpp"

namespace os
{
namespace detail
{
namespace glfw
{

inline os::key::code from_key_impl(int32_t code)
{
	switch(code)
	{
		case GLFW_KEY_ENTER:
			return os::key::enter;
		case GLFW_KEY_ESCAPE:
			return os::key::escape;
		case GLFW_KEY_BACKSPACE:
			return os::key::backspace;
		case GLFW_KEY_TAB:
			return os::key::tab;
		case GLFW_KEY_SPACE:
			return os::key::space;
		case GLFW_KEY_APOSTROPHE:
			return os::key::quote;
		case GLFW_KEY_COMMA:
			return os::key::comma;
		case GLFW_KEY_MINUS:
			return os::key::minus;
		case GLFW_KEY_PERIOD:
			return os::key::period;
		case GLFW_KEY_SLASH:
			return os::key::slash;
		case GLFW_KEY_1:
			return os::key::digit_1;
		case GLFW_KEY_2:
			return os::key::digit_2;
		case GLFW_KEY_3:
			return os::key::digit_3;
		case GLFW_KEY_4:
			return os::key::digit_4;
		case GLFW_KEY_5:
			return os::key::digit_5;
		case GLFW_KEY_6:
			return os::key::digit_6;
		case GLFW_KEY_7:
			return os::key::digit_7;
		case GLFW_KEY_8:
			return os::key::digit_8;
		case GLFW_KEY_9:
			return os::key::digit_9;
		case GLFW_KEY_0:
			return os::key::digit_0;
		case GLFW_KEY_SEMICOLON:
			return os::key::semicolon;
		case GLFW_KEY_LEFT_BRACKET:
			return os::key::leftbracket;
		case GLFW_KEY_BACKSLASH:
			return os::key::backslash;
		case GLFW_KEY_RIGHT_BRACKET:
			return os::key::rightbracket;

		default:
			return os::key::unknown;
	}
}

inline int32_t to_key_impl(os::key::code code)
{
	switch(code)
	{
		case os::key::enter:
			return GLFW_KEY_ENTER;
		case os::key::escape:
			return GLFW_KEY_ESCAPE;
		case os::key::backspace:
			return GLFW_KEY_BACKSPACE;
		case os::key::tab:
			return GLFW_KEY_TAB;
		case os::key::space:
			return GLFW_KEY_SPACE;
		case os::key::quote:
			return GLFW_KEY_APOSTROPHE;
		case os::key::comma:
			return GLFW_KEY_COMMA;
		case os::key::minus:
			return GLFW_KEY_MINUS;
		case os::key::period:
			return GLFW_KEY_PERIOD;
		case os::key::slash:
			return GLFW_KEY_SLASH;
		case os::key::digit_1:
			return GLFW_KEY_1;
		case os::key::digit_2:
			return GLFW_KEY_2;
		case os::key::digit_3:
			return GLFW_KEY_3;
		case os::key::digit_4:
			return GLFW_KEY_4;
		case os::key::digit_5:
			return GLFW_KEY_5;
		case os::key::digit_6:
			return GLFW_KEY_6;
		case os::key::digit_7:
			return GLFW_KEY_7;
		case os::key::digit_8:
			return GLFW_KEY_8;
		case os::key::digit_9:
			return GLFW_KEY_9;
		case os::key::digit_0:
			return GLFW_KEY_0;
		case os::key::semicolon:
			return GLFW_KEY_SEMICOLON;
		case os::key::leftbracket:
			return GLFW_KEY_LEFT_BRACKET;
		case os::key::backslash:
			return GLFW_KEY_BACKSLASH;
		case os::key::rightbracket:
			return GLFW_KEY_RIGHT_BRACKET;

		default:
			return GLFW_KEY_UNKNOWN;
	}
}

namespace key
{

inline os::key::code from_string(const std::string&) noexcept
{
	return from_key_impl(GLFW_KEY_UNKNOWN);
}

inline std::string to_string(os::key::code key_code) noexcept
{
	return glfwGetKeyName(to_key_impl(key_code), 0);
}

inline bool is_pressed(os::key::code key_code) noexcept
{
	return glfwGetKey(nullptr, to_key_impl(key_code)) == GLFW_PRESS;
}
}

inline bool has_screen_keyboard() noexcept
{
	return false;
}

inline void start_text_input() noexcept
{
}

inline void stop_text_input() noexcept
{
}

inline bool is_text_input_active() noexcept
{
	return false;
}
}
}
}
