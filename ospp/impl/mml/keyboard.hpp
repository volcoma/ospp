#include "../../keyboard.h"

#include <mml/window/window.hpp>

namespace os
{
namespace detail
{
namespace mml
{

inline key::code from_layout_independent_impl(::mml::keyboard::key code)
{
	switch(code)
	{
        case ::mml::keyboard::key::A: return key::a;
        case ::mml::keyboard::key::B: return key::b;
        case ::mml::keyboard::key::C: return key::c;
        case ::mml::keyboard::key::D: return key::d;
        case ::mml::keyboard::key::E: return key::e;
        case ::mml::keyboard::key::F: return key::f;
        case ::mml::keyboard::key::G: return key::g;
        case ::mml::keyboard::key::H: return key::h;
        case ::mml::keyboard::key::I: return key::i;
        case ::mml::keyboard::key::J: return key::j;
        case ::mml::keyboard::key::K: return key::k;
        case ::mml::keyboard::key::L: return key::l;
        case ::mml::keyboard::key::M: return key::m;
        case ::mml::keyboard::key::N: return key::n;
        case ::mml::keyboard::key::O: return key::o;
        case ::mml::keyboard::key::P: return key::p;
        case ::mml::keyboard::key::Q: return key::q;
        case ::mml::keyboard::key::R: return key::r;
        case ::mml::keyboard::key::S: return key::s;
        case ::mml::keyboard::key::T: return key::t;
        case ::mml::keyboard::key::U: return key::u;
        case ::mml::keyboard::key::V: return key::v;
        case ::mml::keyboard::key::W: return key::w;
        case ::mml::keyboard::key::X: return key::x;
        case ::mml::keyboard::key::Y: return key::y;
        case ::mml::keyboard::key::Z: return key::z;
        case ::mml::keyboard::key::Num0: return key::digit0;
        case ::mml::keyboard::key::Num1: return key::digit1;
        case ::mml::keyboard::key::Num2: return key::digit2;
        case ::mml::keyboard::key::Num3: return key::digit3;
        case ::mml::keyboard::key::Num4: return key::digit4;
        case ::mml::keyboard::key::Num5: return key::digit5;
        case ::mml::keyboard::key::Num6: return key::digit6;
        case ::mml::keyboard::key::Num7: return key::digit7;
        case ::mml::keyboard::key::Num8: return key::digit8;
        case ::mml::keyboard::key::Num9: return key::digit9;
        case ::mml::keyboard::key::Escape: return key::escape;
        case ::mml::keyboard::key::LControl: return key::lctrl;
        case ::mml::keyboard::key::LShift: return key::lshift;
        case ::mml::keyboard::key::LAlt: return key::lalt;
        case ::mml::keyboard::key::LSystem: return key::lgui;
        case ::mml::keyboard::key::RControl: return key::rctrl;
        case ::mml::keyboard::key::RShift: return key::rshift;
        case ::mml::keyboard::key::RAlt: return key::ralt;
        case ::mml::keyboard::key::RSystem: return key::rgui;
        case ::mml::keyboard::key::Menu: return key::menu;
        case ::mml::keyboard::key::LBracket: return key::leftbracket;
        case ::mml::keyboard::key::RBracket: return key::rightbracket;
        case ::mml::keyboard::key::Semicolon: return key::semicolon;
        case ::mml::keyboard::key::Comma: return key::comma;
        case ::mml::keyboard::key::Period: return key::period;
        case ::mml::keyboard::key::Quote: return key::apostrophe;
        case ::mml::keyboard::key::Slash: return key::slash;
        case ::mml::keyboard::key::Backslash: return key::backslash;
        case ::mml::keyboard::key::Tilde: return key::grave;
        case ::mml::keyboard::key::Equal: return key::equals;
        case ::mml::keyboard::key::Hyphen: return key::minus;
        case ::mml::keyboard::key::Space: return key::space;
        case ::mml::keyboard::key::Enter: return key::enter;
        case ::mml::keyboard::key::Backspace: return key::backspace;
        case ::mml::keyboard::key::Tab: return key::tab;
        case ::mml::keyboard::key::PageUp: return key::pageup;
        case ::mml::keyboard::key::PageDown: return key::pagedown;
        case ::mml::keyboard::key::End: return key::end;
        case ::mml::keyboard::key::Home: return key::home;
        case ::mml::keyboard::key::Insert: return key::insert;
        case ::mml::keyboard::key::Delete: return key::del;
        case ::mml::keyboard::key::Add: return key::kp_plus;
        case ::mml::keyboard::key::Subtract: return key::minus;
        case ::mml::keyboard::key::Multiply: return key::kp_multiply;
        case ::mml::keyboard::key::Divide: return key::kp_divide;
        case ::mml::keyboard::key::Left: return key::left;
        case ::mml::keyboard::key::Right: return key::right;
        case ::mml::keyboard::key::Up: return key::up;
        case ::mml::keyboard::key::Down: return key::down;
        case ::mml::keyboard::key::Numpad0: return key::kp_digit0;
        case ::mml::keyboard::key::Numpad1: return key::kp_digit1;
        case ::mml::keyboard::key::Numpad2: return key::kp_digit2;
        case ::mml::keyboard::key::Numpad3: return key::kp_digit3;
        case ::mml::keyboard::key::Numpad4: return key::kp_digit4;
        case ::mml::keyboard::key::Numpad5: return key::kp_digit5;
        case ::mml::keyboard::key::Numpad6: return key::kp_digit6;
        case ::mml::keyboard::key::Numpad7: return key::kp_digit7;
        case ::mml::keyboard::key::Numpad8: return key::kp_digit8;
        case ::mml::keyboard::key::Numpad9: return key::kp_digit9;
        case ::mml::keyboard::key::F1: return key::f1;
        case ::mml::keyboard::key::F2: return key::f2;
        case ::mml::keyboard::key::F3: return key::f3;
        case ::mml::keyboard::key::F4: return key::f4;
        case ::mml::keyboard::key::F5: return key::f5;
        case ::mml::keyboard::key::F6: return key::f6;
        case ::mml::keyboard::key::F7: return key::f7;
        case ::mml::keyboard::key::F8: return key::f8;
        case ::mml::keyboard::key::F9: return key::f9;
        case ::mml::keyboard::key::F10: return key::f10;
        case ::mml::keyboard::key::F11: return key::f11;
        case ::mml::keyboard::key::F12: return key::f12;
        case ::mml::keyboard::key::F13: return key::f13;
        case ::mml::keyboard::key::F14: return key::f14;
        case ::mml::keyboard::key::F15: return key::f15;
        case ::mml::keyboard::key::Pause: return key::pause;

		default:
			return key::unknown;
	}
}

inline ::mml::keyboard::key to_layout_independent_impl(key::code code)
{
	switch(code)
	{
        case key::a: return ::mml::keyboard::key::A;
        case key::b: return ::mml::keyboard::key::B;
        case key::c: return ::mml::keyboard::key::C;
        case key::d: return ::mml::keyboard::key::D;
        case key::e: return ::mml::keyboard::key::E;
        case key::f: return ::mml::keyboard::key::F;
        case key::g: return ::mml::keyboard::key::G;
        case key::h: return ::mml::keyboard::key::H;
        case key::i: return ::mml::keyboard::key::I;
        case key::j: return ::mml::keyboard::key::J;
        case key::k: return ::mml::keyboard::key::K;
        case key::l: return ::mml::keyboard::key::L;
        case key::m: return ::mml::keyboard::key::M;
        case key::n: return ::mml::keyboard::key::N;
        case key::o: return ::mml::keyboard::key::O;
        case key::p: return ::mml::keyboard::key::P;
        case key::q: return ::mml::keyboard::key::Q;
        case key::r: return ::mml::keyboard::key::R;
        case key::s: return ::mml::keyboard::key::S;
        case key::t: return ::mml::keyboard::key::T;
        case key::u: return ::mml::keyboard::key::U;
        case key::v: return ::mml::keyboard::key::V;
        case key::w: return ::mml::keyboard::key::W;
        case key::x: return ::mml::keyboard::key::X;
        case key::y: return ::mml::keyboard::key::Y;
        case key::z: return ::mml::keyboard::key::Z;
        case key::digit0: return ::mml::keyboard::key::Num0;
        case key::digit1: return ::mml::keyboard::key::Num1;
        case key::digit2: return ::mml::keyboard::key::Num2;
        case key::digit3: return ::mml::keyboard::key::Num3;
        case key::digit4: return ::mml::keyboard::key::Num4;
        case key::digit5: return ::mml::keyboard::key::Num5;
        case key::digit6: return ::mml::keyboard::key::Num6;
        case key::digit7: return ::mml::keyboard::key::Num7;
        case key::digit8: return ::mml::keyboard::key::Num8;
        case key::digit9: return ::mml::keyboard::key::Num9;
        case key::escape: return ::mml::keyboard::key::Escape;
        case key::lctrl: return ::mml::keyboard::key::LControl;
        case key::lshift: return ::mml::keyboard::key::LShift;
        case key::lalt: return ::mml::keyboard::key::LAlt;
        case key::lgui: return ::mml::keyboard::key::LSystem;
        case key::rctrl: return ::mml::keyboard::key::RControl;
        case key::rshift: return ::mml::keyboard::key::RShift;
        case key::ralt: return ::mml::keyboard::key::RAlt;
        case key::rgui: return ::mml::keyboard::key::RSystem;
        case key::menu: return ::mml::keyboard::key::Menu;
        case key::leftbracket: return ::mml::keyboard::key::LBracket;
        case key::rightbracket: return ::mml::keyboard::key::RBracket;
        case key::semicolon: return ::mml::keyboard::key::Semicolon;
        case key::comma: return ::mml::keyboard::key::Comma;
        case key::period: return ::mml::keyboard::key::Period;
        case key::apostrophe: return ::mml::keyboard::key::Quote;
        case key::slash: return ::mml::keyboard::key::Slash;
        case key::backslash: return ::mml::keyboard::key::Backslash;
        case key::grave: return ::mml::keyboard::key::Tilde;
        case key::equals: return ::mml::keyboard::key::Equal;
        case key::space: return ::mml::keyboard::key::Space;
        case key::enter: return ::mml::keyboard::key::Enter;
        case key::backspace: return ::mml::keyboard::key::Backspace;
        case key::tab: return ::mml::keyboard::key::Tab;
        case key::pageup: return ::mml::keyboard::key::PageUp;
        case key::pagedown: return ::mml::keyboard::key::PageDown;
        case key::end: return ::mml::keyboard::key::End;
        case key::home: return ::mml::keyboard::key::Home;
        case key::insert: return ::mml::keyboard::key::Insert;
        case key::del: return ::mml::keyboard::key::Delete;
        case key::kp_plus: return ::mml::keyboard::key::Add;
        case key::minus: return ::mml::keyboard::key::Subtract;
        case key::kp_multiply: return ::mml::keyboard::key::Multiply;
        case key::kp_divide: return ::mml::keyboard::key::Divide;
        case key::left: return ::mml::keyboard::key::Left;
        case key::right: return ::mml::keyboard::key::Right;
        case key::up: return ::mml::keyboard::key::Up;
        case key::down: return ::mml::keyboard::key::Down;
        case key::kp_digit0: return ::mml::keyboard::key::Numpad0;
        case key::kp_digit1: return ::mml::keyboard::key::Numpad1;
        case key::kp_digit2: return ::mml::keyboard::key::Numpad2;
        case key::kp_digit3: return ::mml::keyboard::key::Numpad3;
        case key::kp_digit4: return ::mml::keyboard::key::Numpad4;
        case key::kp_digit5: return ::mml::keyboard::key::Numpad5;
        case key::kp_digit6: return ::mml::keyboard::key::Numpad6;
        case key::kp_digit7: return ::mml::keyboard::key::Numpad7;
        case key::kp_digit8: return ::mml::keyboard::key::Numpad8;
        case key::kp_digit9: return ::mml::keyboard::key::Numpad9;
        case key::f1: return ::mml::keyboard::key::F1;
        case key::f2: return ::mml::keyboard::key::F2;
        case key::f3: return ::mml::keyboard::key::F3;
        case key::f4: return ::mml::keyboard::key::F4;
        case key::f5: return ::mml::keyboard::key::F5;
        case key::f6: return ::mml::keyboard::key::F6;
        case key::f7: return ::mml::keyboard::key::F7;
        case key::f8: return ::mml::keyboard::key::F8;
        case key::f9: return ::mml::keyboard::key::F9;
        case key::f10: return ::mml::keyboard::key::F10;
        case key::f11: return ::mml::keyboard::key::F11;
        case key::f12: return ::mml::keyboard::key::F12;
        case key::f13: return ::mml::keyboard::key::F13;
        case key::f14: return ::mml::keyboard::key::F14;
        case key::f15: return ::mml::keyboard::key::F15;
        case key::pause: return ::mml::keyboard::key::Pause;

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

inline std::string to_string(os::key::code) noexcept
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
