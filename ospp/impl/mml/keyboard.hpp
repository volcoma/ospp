#include "../../keyboard.h"

#include <mml/window/window.hpp>

namespace os
{
namespace detail
{
namespace mml
{

inline os::key::code from_layout_independent_impl(::mml::keyboard::key code)
{
	switch(code)
	{
			//		case SDLK_RETURN:
			//			return os::key::enter;
			//		case SDLK_ESCAPE:
			//			return os::key::escape;
			//		case SDLK_BACKSPACE:
			//			return os::key::backspace;
			//		case SDLK_TAB:
			//			return os::key::tab;
			//		case SDLK_SPACE:
			//			return os::key::space;
			//		case SDLK_EXCLAIM:
			//			return os::key::exclaim;
			//		case SDLK_QUOTEDBL:
			//			return os::key::quotedbl;
			//		case SDLK_HASH:
			//			return os::key::hash;
			//		case SDLK_PERCENT:
			//			return os::key::percent;
			//		case SDLK_DOLLAR:
			//			return os::key::dollar;
			//		case SDLK_AMPERSAND:
			//			return os::key::ampersand;
			//		case SDLK_QUOTE:
			//			return os::key::quote;
			//		case SDLK_LEFTPAREN:
			//			return os::key::leftparen;
			//		case SDLK_RIGHTPAREN:
			//			return os::key::rightparen;
			//		case SDLK_ASTERISK:
			//			return os::key::asterisk;
			//		case SDLK_PLUS:
			//			return os::key::plus;
			//		case SDLK_COMMA:
			//			return os::key::comma;
			//		case SDLK_MINUS:
			//			return os::key::minus;
			//		case SDLK_PERIOD:
			//			return os::key::period;
			//		case SDLK_SLASH:
			//			return os::key::slash;
			//		case SDLK_1:
			//			return os::key::digit_1;
			//		case SDLK_2:
			//			return os::key::digit_2;
			//		case SDLK_3:
			//			return os::key::digit_3;
			//		case SDLK_4:
			//			return os::key::digit_4;
			//		case SDLK_5:
			//			return os::key::digit_5;
			//		case SDLK_6:
			//			return os::key::digit_6;
			//		case SDLK_7:
			//			return os::key::digit_7;
			//		case SDLK_8:
			//			return os::key::digit_8;
			//		case SDLK_9:
			//			return os::key::digit_9;
			//		case SDLK_0:
			//			return os::key::digit_0;
			//		case SDLK_COLON:
			//			return os::key::colon;
			//		case SDLK_SEMICOLON:
			//			return os::key::semicolon;
			//		case SDLK_LESS:
			//			return os::key::less;
			//		case SDLK_EQUALS:
			//			return os::key::equals;
			//		case SDLK_GREATER:
			//			return os::key::greater;
			//		case SDLK_QUESTION:
			//			return os::key::question;
			//		case SDLK_AT:
			//			return os::key::at;
			//		case SDLK_LEFTBRACKET:
			//			return os::key::leftbracket;
			//		case SDLK_BACKSLASH:
			//			return os::key::backslash;
			//		case SDLK_RIGHTBRACKET:
			//			return os::key::rightbracket;
			//		case SDLK_CARET:
			//			return os::key::caret;
			//		case SDLK_UNDERSCORE:
			//			return os::key::underscore;
			//		case SDLK_BACKQUOTE:
			//			return os::key::backquote;

		default:
			return os::key::unknown;
	}
}

inline ::mml::keyboard::key to_layout_independent_impl(os::key::code code)
{
	switch(code)
	{
			//		case os::key::enter:
			//			return SDLK_RETURN;
			//		case os::key::escape:
			//			return SDLK_ESCAPE;
			//		case os::key::backspace:
			//			return SDLK_BACKSPACE;
			//		case os::key::tab:
			//			return SDLK_TAB;
			//		case os::key::space:
			//			return SDLK_SPACE;
			//		case os::key::exclaim:
			//			return SDLK_EXCLAIM;
			//		case os::key::quotedbl:
			//			return SDLK_QUOTEDBL;
			//		case os::key::hash:
			//			return SDLK_HASH;
			//		case os::key::percent:
			//			return SDLK_PERCENT;
			//		case os::key::dollar:
			//			return SDLK_DOLLAR;
			//		case os::key::ampersand:
			//			return SDLK_AMPERSAND;
			//		case os::key::quote:
			//			return SDLK_QUOTE;
			//		case os::key::leftparen:
			//			return SDLK_LEFTPAREN;
			//		case os::key::rightparen:
			//			return SDLK_RIGHTPAREN;
			//		case os::key::asterisk:
			//			return SDLK_ASTERISK;
			//		case os::key::plus:
			//			return SDLK_PLUS;
			//		case os::key::comma:
			//			return SDLK_COMMA;
			//		case os::key::minus:
			//			return SDLK_MINUS;
			//		case os::key::period:
			//			return SDLK_PERIOD;
			//		case os::key::slash:
			//			return SDLK_SLASH;
			//		case os::key::digit_1:
			//			return SDLK_1;
			//		case os::key::digit_2:
			//			return SDLK_2;
			//		case os::key::digit_3:
			//			return SDLK_3;
			//		case os::key::digit_4:
			//			return SDLK_4;
			//		case os::key::digit_5:
			//			return SDLK_5;
			//		case os::key::digit_6:
			//			return SDLK_6;
			//		case os::key::digit_7:
			//			return SDLK_7;
			//		case os::key::digit_8:
			//			return SDLK_8;
			//		case os::key::digit_9:
			//			return SDLK_9;
			//		case os::key::digit_0:
			//			return SDLK_0;
			//		case os::key::colon:
			//			return SDLK_COLON;
			//		case os::key::semicolon:
			//			return SDLK_SEMICOLON;
			//		case os::key::less:
			//			return SDLK_LESS;
			//		case os::key::equals:
			//			return SDLK_EQUALS;
			//		case os::key::greater:
			//			return SDLK_GREATER;
			//		case os::key::question:
			//			return SDLK_QUESTION;
			//		case os::key::at:
			//			return SDLK_AT;
			//		case os::key::leftbracket:
			//			return SDLK_LEFTBRACKET;
			//		case os::key::backslash:
			//			return SDLK_BACKSLASH;
			//		case os::key::rightbracket:
			//			return SDLK_RIGHTBRACKET;
			//		case os::key::caret:
			//			return SDLK_CARET;
			//		case os::key::underscore:
			//			return SDLK_UNDERSCORE;
			//		case os::key::backquote:
			//			return SDLK_BACKQUOTE;

		default:
			return ::mml::keyboard::Unknown;
	}
}

namespace key
{
inline os::key::code from_string(const std::string&) noexcept
{
	return from_layout_independent_impl(::mml::keyboard::Unknown);
}

inline std::string to_string(os::key::code key_code) noexcept
{
	return {};
}

inline bool is_pressed(os::key::code key_code) noexcept
{
	return ::mml::keyboard::is_key_pressed(to_layout_independent_impl(key_code));
}
}

inline bool has_screen_keyboard() noexcept
{
	return false;
}

inline void start_text_input() noexcept
{
	::mml::keyboard::set_virtual_keyboard_visible(true);
}

inline void stop_text_input() noexcept
{
	::mml::keyboard::set_virtual_keyboard_visible(false);
}

inline bool is_text_input_active() noexcept
{
	return false;
}
}
}
}
