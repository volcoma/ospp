////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <mml/window/unix/key_sym_to_key_mapping.hpp>

#include <X11/keysym.h>

namespace mml
{
namespace priv
{

////////////////////////////////////////////////////////////
keyboard::key key_sym_to_key(KeySym symbol)
{
	// clang-format off
	switch (symbol)
	{
		case XK_Shift_L:      return keyboard::LShift;
		case XK_Shift_R:      return keyboard::RShift;
		case XK_Control_L:    return keyboard::LControl;
		case XK_Control_R:    return keyboard::RControl;
		case XK_Alt_L:        return keyboard::LAlt;
		case XK_ISO_Level3_Shift:
		case XK_Alt_R:        return keyboard::RAlt;
		case XK_Super_L:      return keyboard::LSystem;
		case XK_Super_R:      return keyboard::RSystem;
		case XK_Menu:         return keyboard::Menu;
		case XK_Escape:       return keyboard::Escape;
		case XK_semicolon:    return keyboard::Semicolon;
		case XK_slash:        return keyboard::Slash;
		case XK_equal:        return keyboard::Equal;
		case XK_minus:        return keyboard::Hyphen;
		case XK_bracketleft:  return keyboard::LBracket;
		case XK_bracketright: return keyboard::RBracket;
		case XK_comma:        return keyboard::Comma;
		case XK_period:       return keyboard::Period;
		case XK_apostrophe:   return keyboard::Apostrophe;
		case XK_backslash:    return keyboard::Backslash;
		case XK_grave:        return keyboard::Grave;
		case XK_space:        return keyboard::Space;
		case XK_Return:       return keyboard::Enter;
		case XK_KP_Enter:     return keyboard::Enter;
		case XK_BackSpace:    return keyboard::Backspace;
		case XK_Tab:          return keyboard::Tab;
		case XK_Prior:        return keyboard::PageUp;
		case XK_Next:         return keyboard::PageDown;
		case XK_End:          return keyboard::End;
		case XK_Home:         return keyboard::Home;
		case XK_Insert:       return keyboard::Insert;
		case XK_Delete:       return keyboard::Delete;
		case XK_KP_Add:       return keyboard::Add;
		case XK_KP_Subtract:  return keyboard::Subtract;
		case XK_KP_Multiply:  return keyboard::Multiply;
		case XK_KP_Divide:    return keyboard::Divide;
		case XK_KP_Delete:    return keyboard::Period;
		case XK_Pause:        return keyboard::Pause;
		case XK_F1:           return keyboard::F1;
		case XK_F2:           return keyboard::F2;
		case XK_F3:           return keyboard::F3;
		case XK_F4:           return keyboard::F4;
		case XK_F5:           return keyboard::F5;
		case XK_F6:           return keyboard::F6;
		case XK_F7:           return keyboard::F7;
		case XK_F8:           return keyboard::F8;
		case XK_F9:           return keyboard::F9;
		case XK_F10:          return keyboard::F10;
		case XK_F11:          return keyboard::F11;
		case XK_F12:          return keyboard::F12;
		case XK_F13:          return keyboard::F13;
		case XK_F14:          return keyboard::F14;
		case XK_F15:          return keyboard::F15;
		case XK_Left:         return keyboard::Left;
		case XK_Right:        return keyboard::Right;
		case XK_Up:           return keyboard::Up;
		case XK_Down:         return keyboard::Down;
		case XK_KP_Insert:    return keyboard::Numpad0;
		case XK_KP_End:       return keyboard::Numpad1;
		case XK_KP_Down:      return keyboard::Numpad2;
		case XK_KP_Page_Down: return keyboard::Numpad3;
		case XK_KP_Left:      return keyboard::Numpad4;
		case XK_KP_Begin:     return keyboard::Numpad5;
		case XK_KP_Right:     return keyboard::Numpad6;
		case XK_KP_Home:      return keyboard::Numpad7;
		case XK_KP_Up:        return keyboard::Numpad8;
		case XK_KP_Page_Up:   return keyboard::Numpad9;
		case XK_a:            return keyboard::A;
		case XK_b:            return keyboard::B;
		case XK_c:            return keyboard::C;
		case XK_d:            return keyboard::D;
		case XK_e:            return keyboard::E;
		case XK_f:            return keyboard::F;
		case XK_g:            return keyboard::G;
		case XK_h:            return keyboard::H;
		case XK_i:            return keyboard::I;
		case XK_j:            return keyboard::J;
		case XK_k:            return keyboard::K;
		case XK_l:            return keyboard::L;
		case XK_m:            return keyboard::M;
		case XK_n:            return keyboard::N;
		case XK_o:            return keyboard::O;
		case XK_p:            return keyboard::P;
		case XK_q:            return keyboard::Q;
		case XK_r:            return keyboard::R;
		case XK_s:            return keyboard::S;
		case XK_t:            return keyboard::T;
		case XK_u:            return keyboard::U;
		case XK_v:            return keyboard::V;
		case XK_w:            return keyboard::W;
		case XK_x:            return keyboard::X;
		case XK_y:            return keyboard::Y;
		case XK_z:            return keyboard::Z;
		case XK_0:            return keyboard::Num0;
		case XK_1:            return keyboard::Num1;
		case XK_2:            return keyboard::Num2;
		case XK_3:            return keyboard::Num3;
		case XK_4:            return keyboard::Num4;
		case XK_5:            return keyboard::Num5;
		case XK_6:            return keyboard::Num6;
		case XK_7:            return keyboard::Num7;
		case XK_8:            return keyboard::Num8;
		case XK_9:            return keyboard::Num9;
		default:              return keyboard::Unknown;
	}
	// clang-format on
}

////////////////////////////////////////////////////////////
KeySym key_to_key_sym(keyboard::key key)
{
	// clang-format off
	switch (key)
	{
		case keyboard::LShift:     return XK_Shift_L;
		case keyboard::RShift:     return XK_Shift_R;
		case keyboard::LControl:   return XK_Control_L;
		case keyboard::RControl:   return XK_Control_R;
		case keyboard::LAlt:       return XK_Alt_L;
		case keyboard::RAlt:       return XK_Alt_R;
		case keyboard::LSystem:    return XK_Super_L;
		case keyboard::RSystem:    return XK_Super_R;
		case keyboard::Menu:       return XK_Menu;
		case keyboard::Escape:     return XK_Escape;
		case keyboard::Semicolon:  return XK_semicolon;
		case keyboard::Slash:      return XK_slash;
		case keyboard::Equal:      return XK_equal;
		case keyboard::Hyphen:     return XK_minus;
		case keyboard::LBracket:   return XK_bracketleft;
		case keyboard::RBracket:   return XK_bracketright;
		case keyboard::Comma:      return XK_comma;
		case keyboard::Period:     return XK_period;
		case keyboard::Apostrophe: return XK_apostrophe;
		case keyboard::Backslash:  return XK_backslash;
		case keyboard::Grave:      return XK_grave;
		case keyboard::Space:      return XK_space;
		case keyboard::Enter:      return XK_Return;
		case keyboard::Backspace:  return XK_BackSpace;
		case keyboard::Tab:        return XK_Tab;
		case keyboard::PageUp:     return XK_Prior;
		case keyboard::PageDown:   return XK_Next;
		case keyboard::End:        return XK_End;
		case keyboard::Home:       return XK_Home;
		case keyboard::Insert:     return XK_Insert;
		case keyboard::Delete:     return XK_Delete;
		case keyboard::Add:        return XK_KP_Add;
		case keyboard::Subtract:   return XK_KP_Subtract;
		case keyboard::Multiply:   return XK_KP_Multiply;
		case keyboard::Divide:     return XK_KP_Divide;
		case keyboard::Pause:      return XK_Pause;
		case keyboard::F1:         return XK_F1;
		case keyboard::F2:         return XK_F2;
		case keyboard::F3:         return XK_F3;
		case keyboard::F4:         return XK_F4;
		case keyboard::F5:         return XK_F5;
		case keyboard::F6:         return XK_F6;
		case keyboard::F7:         return XK_F7;
		case keyboard::F8:         return XK_F8;
		case keyboard::F9:         return XK_F9;
		case keyboard::F10:        return XK_F10;
		case keyboard::F11:        return XK_F11;
		case keyboard::F12:        return XK_F12;
		case keyboard::F13:        return XK_F13;
		case keyboard::F14:        return XK_F14;
		case keyboard::F15:        return XK_F15;
		case keyboard::Left:       return XK_Left;
		case keyboard::Right:      return XK_Right;
		case keyboard::Up:         return XK_Up;
		case keyboard::Down:       return XK_Down;
		case keyboard::Numpad0:    return XK_KP_Insert;
		case keyboard::Numpad1:    return XK_KP_End;
		case keyboard::Numpad2:    return XK_KP_Down;
		case keyboard::Numpad3:    return XK_KP_Page_Down;
		case keyboard::Numpad4:    return XK_KP_Left;
		case keyboard::Numpad5:    return XK_KP_Begin;
		case keyboard::Numpad6:    return XK_KP_Right;
		case keyboard::Numpad7:    return XK_KP_Home;
		case keyboard::Numpad8:    return XK_KP_Up;
		case keyboard::Numpad9:    return XK_KP_Page_Up;
		case keyboard::A:          return XK_a;
		case keyboard::B:          return XK_b;
		case keyboard::C:          return XK_c;
		case keyboard::D:          return XK_d;
		case keyboard::E:          return XK_e;
		case keyboard::F:          return XK_f;
		case keyboard::G:          return XK_g;
		case keyboard::H:          return XK_h;
		case keyboard::I:          return XK_i;
		case keyboard::J:          return XK_j;
		case keyboard::K:          return XK_k;
		case keyboard::L:          return XK_l;
		case keyboard::M:          return XK_m;
		case keyboard::N:          return XK_n;
		case keyboard::O:          return XK_o;
		case keyboard::P:          return XK_p;
		case keyboard::Q:          return XK_q;
		case keyboard::R:          return XK_r;
		case keyboard::S:          return XK_s;
		case keyboard::T:          return XK_t;
		case keyboard::U:          return XK_u;
		case keyboard::V:          return XK_v;
		case keyboard::W:          return XK_w;
		case keyboard::X:          return XK_x;
		case keyboard::Y:          return XK_y;
		case keyboard::Z:          return XK_z;
		case keyboard::Num0:       return XK_0;
		case keyboard::Num1:       return XK_1;
		case keyboard::Num2:       return XK_2;
		case keyboard::Num3:       return XK_3;
		case keyboard::Num4:       return XK_4;
		case keyboard::Num5:       return XK_5;
		case keyboard::Num6:       return XK_6;
		case keyboard::Num7:       return XK_7;
		case keyboard::Num8:       return XK_8;
		case keyboard::Num9:       return XK_9;
		default:                   return NoSymbol;
	}
	// clang-format on
}
} // namespace priv
} // namespace mml
