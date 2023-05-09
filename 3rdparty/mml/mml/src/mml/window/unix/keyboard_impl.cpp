#include <mml/window/unix/display.hpp>
#include <mml/window/unix/key_sym_to_key_mapping.hpp>
#include <mml/window/unix/key_sym_to_unicode_mapping.hpp>
#include <mml/window/unix/keyboard_impl.hpp>

#include <mml/system/utf.hpp>

#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <cstring>

namespace mml
{
namespace priv
{

namespace
{

const KeyCode nullKeyCode = 0;
const int maxKeyCode = 256;
KeyCode scancode_to_keycode_mapping[static_cast<std::size_t>(
	keyboard::scan::ScancodeCount)];						 ///< Mapping of SFML scancode to X11 KeyCode
keyboard::scancode key_code_to_scancode_mapping[maxKeyCode]; ///< Mapping of X11 KeyCode to SFML scancode

////////////////////////////////////////////////////////////
bool is_valid_keycode(KeyCode keycode)
{
	// Valid key code range is [8,255], according to the Xlib manual
	return keycode >= 8;
}

////////////////////////////////////////////////////////////
keyboard::scancode translate_keycode(Display* display, KeyCode keycode)
{
	if(!is_valid_keycode(keycode))
		return keyboard::scan::Unknown;

	// Try secondary keysym, for numeric keypad keys
	// Note: This way we always force "NumLock = ON", which is intentional
	// since the returned key code should correspond to a physical location.
	KeySym keySym = XkbKeycodeToKeysym(display, keycode, 0, 1);

	// clang-format off
	switch (keySym)
	{
		case XK_KP_0:         return keyboard::scan::Numpad0;
		case XK_KP_1:         return keyboard::scan::Numpad1;
		case XK_KP_2:         return keyboard::scan::Numpad2;
		case XK_KP_3:         return keyboard::scan::Numpad3;
		case XK_KP_4:         return keyboard::scan::Numpad4;
		case XK_KP_5:         return keyboard::scan::Numpad5;
		case XK_KP_6:         return keyboard::scan::Numpad6;
		case XK_KP_7:         return keyboard::scan::Numpad7;
		case XK_KP_8:         return keyboard::scan::Numpad8;
		case XK_KP_9:         return keyboard::scan::Numpad9;
		case XK_KP_Separator: return keyboard::scan::NumpadDecimal;
		case XK_KP_Decimal:   return keyboard::scan::NumpadDecimal;
		case XK_KP_Equal:     return keyboard::scan::NumpadEqual;
		case XK_KP_Enter:     return keyboard::scan::NumpadEnter;
		default:              break;
	}
	// clang-format on

	// Now try primary keysym for function keys (non-printable keys)
	// These should not depend on the current keyboard layout
	keySym = XkbKeycodeToKeysym(display, keycode, 0, 0);

	// clang-format off
	switch (keySym)
	{
		case XK_Return:           return keyboard::scan::Enter;
		case XK_Escape:           return keyboard::scan::Escape;
		case XK_BackSpace:        return keyboard::scan::Backspace;
		case XK_Tab:              return keyboard::scan::Tab;
		case XK_Shift_L:          return keyboard::scan::LShift;
		case XK_Shift_R:          return keyboard::scan::RShift;
		case XK_Control_L:        return keyboard::scan::LControl;
		case XK_Control_R:        return keyboard::scan::RControl;
		case XK_Alt_L:            return keyboard::scan::LAlt;
		case XK_ISO_Level3_Shift: // AltGr on at least some machines
		case XK_Alt_R:            return keyboard::scan::RAlt;
		case XK_Meta_L:
		case XK_Super_L:          return keyboard::scan::LSystem;
		case XK_Meta_R:
		case XK_Super_R:          return keyboard::scan::RSystem;
		case XK_Menu:             return keyboard::scan::Menu;

		case XK_Num_Lock:         return keyboard::scan::NumLock;
		case XK_Caps_Lock:        return keyboard::scan::CapsLock;
		case XK_Execute:          return keyboard::scan::Execute;
		case XK_Hyper_R:          return keyboard::scan::Application;
		case XK_Select:           return keyboard::scan::Select;
		case XK_Cancel:           return keyboard::scan::Stop;
		case XK_Redo:             return keyboard::scan::Redo;
		case XK_Undo:             return keyboard::scan::Undo;
		case XK_Find:             return keyboard::scan::Search;
		case XK_Mode_switch:      return keyboard::scan::ModeChange;

		case XK_Print:            return keyboard::scan::PrintScreen;
		case XK_Scroll_Lock:      return keyboard::scan::ScrollLock;
		case XK_Pause:
		case XK_Break:            return keyboard::scan::Pause;

		case XK_Delete:
		case XK_Clear:            return keyboard::scan::Delete;
		case XK_Home:             return keyboard::scan::Home;
		case XK_End:              return keyboard::scan::End;
		case XK_Page_Up:          return keyboard::scan::PageUp;
		case XK_Page_Down:        return keyboard::scan::PageDown;
		case XK_Insert:           return keyboard::scan::Insert;

		case XK_Left:             return keyboard::scan::Left;
		case XK_Right:            return keyboard::scan::Right;
		case XK_Down:             return keyboard::scan::Down;
		case XK_Up:               return keyboard::scan::Up;

		case XK_F1:               return keyboard::scan::F1;
		case XK_F2:               return keyboard::scan::F2;
		case XK_F3:               return keyboard::scan::F3;
		case XK_F4:               return keyboard::scan::F4;
		case XK_F5:               return keyboard::scan::F5;
		case XK_F6:               return keyboard::scan::F6;
		case XK_F7:               return keyboard::scan::F7;
		case XK_F8:               return keyboard::scan::F8;
		case XK_F9:               return keyboard::scan::F9;
		case XK_F10:              return keyboard::scan::F10;
		case XK_F11:              return keyboard::scan::F11;
		case XK_F12:              return keyboard::scan::F12;
		case XK_F13:              return keyboard::scan::F13;
		case XK_F14:              return keyboard::scan::F14;
		case XK_F15:              return keyboard::scan::F15;
		case XK_F16:              return keyboard::scan::F16;
		case XK_F17:              return keyboard::scan::F17;
		case XK_F18:              return keyboard::scan::F18;
		case XK_F19:              return keyboard::scan::F19;
		case XK_F20:              return keyboard::scan::F20;
		case XK_F21:              return keyboard::scan::F21;
		case XK_F22:              return keyboard::scan::F22;
		case XK_F23:              return keyboard::scan::F23;
		case XK_F24:              return keyboard::scan::F24;

				   // Numeric keypad
		case XK_KP_Divide:        return keyboard::scan::NumpadDivide;
		case XK_KP_Multiply:      return keyboard::scan::NumpadMultiply;
		case XK_KP_Subtract:      return keyboard::scan::NumpadMinus;
		case XK_KP_Add:           return keyboard::scan::NumpadPlus;

				   // These should have been detected in secondary keysym test above!
		case XK_KP_Insert:        return keyboard::scan::Numpad0;
		case XK_KP_End:           return keyboard::scan::Numpad1;
		case XK_KP_Down:          return keyboard::scan::Numpad2;
		case XK_KP_Page_Down:     return keyboard::scan::Numpad3;
		case XK_KP_Left:          return keyboard::scan::Numpad4;
		case XK_KP_Right:         return keyboard::scan::Numpad6;
		case XK_KP_Home:          return keyboard::scan::Numpad7;
		case XK_KP_Up:            return keyboard::scan::Numpad8;
		case XK_KP_Page_Up:       return keyboard::scan::Numpad9;
		case XK_KP_Delete:        return keyboard::scan::NumpadDecimal;
		case XK_KP_Equal:         return keyboard::scan::NumpadEqual;
		case XK_KP_Enter:         return keyboard::scan::NumpadEnter;

				   // Last resort: Check for printable keys (should not happen if the XKB
				   // extension is available). This will give a layout dependent mapping
				   // (which is wrong, and we may miss some keys, especially on non-US
				   // keyboards), but it's better than nothing...
		case XK_a:
		case XK_A:                return keyboard::scan::A;
		case XK_b:
		case XK_B:                return keyboard::scan::B;
		case XK_c:
		case XK_C:                return keyboard::scan::C;
		case XK_d:
		case XK_D:                return keyboard::scan::D;
		case XK_e:
		case XK_E:                return keyboard::scan::E;
		case XK_f:
		case XK_F:                return keyboard::scan::F;
		case XK_g:
		case XK_G:                return keyboard::scan::G;
		case XK_h:
		case XK_H:                return keyboard::scan::H;
		case XK_i:
		case XK_I:                return keyboard::scan::I;
		case XK_j:
		case XK_J:                return keyboard::scan::J;
		case XK_k:
		case XK_K:                return keyboard::scan::K;
		case XK_l:
		case XK_L:                return keyboard::scan::L;
		case XK_m:
		case XK_M:                return keyboard::scan::M;
		case XK_n:
		case XK_N:                return keyboard::scan::N;
		case XK_o:
		case XK_O:                return keyboard::scan::O;
		case XK_p:
		case XK_P:                return keyboard::scan::P;
		case XK_q:
		case XK_Q:                return keyboard::scan::Q;
		case XK_r:
		case XK_R:                return keyboard::scan::R;
		case XK_s:
		case XK_S:                return keyboard::scan::S;
		case XK_t:
		case XK_T:                return keyboard::scan::T;
		case XK_u:
		case XK_U:                return keyboard::scan::U;
		case XK_v:
		case XK_V:                return keyboard::scan::V;
		case XK_w:
		case XK_W:                return keyboard::scan::W;
		case XK_x:
		case XK_X:                return keyboard::scan::X;
		case XK_y:
		case XK_Y:                return keyboard::scan::Y;
		case XK_z:
		case XK_Z:                return keyboard::scan::Z;

		case XK_1:                return keyboard::scan::Num1;
		case XK_2:                return keyboard::scan::Num2;
		case XK_3:                return keyboard::scan::Num3;
		case XK_4:                return keyboard::scan::Num4;
		case XK_5:                return keyboard::scan::Num5;
		case XK_6:                return keyboard::scan::Num6;
		case XK_7:                return keyboard::scan::Num7;
		case XK_8:                return keyboard::scan::Num8;
		case XK_9:                return keyboard::scan::Num9;
		case XK_0:                return keyboard::scan::Num0;

		case XK_space:            return keyboard::scan::Space;
		case XK_minus:            return keyboard::scan::Hyphen;
		case XK_equal:            return keyboard::scan::Equal;
		case XK_bracketleft:      return keyboard::scan::LBracket;
		case XK_bracketright:     return keyboard::scan::RBracket;
		case XK_backslash:        return keyboard::scan::Backslash;
		case XK_semicolon:        return keyboard::scan::Semicolon;
		case XK_apostrophe:       return keyboard::scan::Apostrophe;
		case XK_grave:            return keyboard::scan::Grave;
		case XK_comma:            return keyboard::scan::Comma;
		case XK_period:           return keyboard::scan::Period;
		case XK_slash:            return keyboard::scan::Slash;
		case XK_less:             return keyboard::scan::NonUsBackslash;

		default:                  return keyboard::scan::Unknown;
	}
	// clang-format on
}

////////////////////////////////////////////////////////////
std::unordered_map<std::string, keyboard::scancode> get_name_scancode_map()
{
	std::unordered_map<std::string, keyboard::scancode> mapping;

	mapping.emplace("LSGT", keyboard::scan::NonUsBackslash);

	mapping.emplace("TLDE", keyboard::scan::Grave);
	mapping.emplace("AE01", keyboard::scan::Num1);
	mapping.emplace("AE02", keyboard::scan::Num2);
	mapping.emplace("AE03", keyboard::scan::Num3);
	mapping.emplace("AE04", keyboard::scan::Num4);
	mapping.emplace("AE05", keyboard::scan::Num5);
	mapping.emplace("AE06", keyboard::scan::Num6);
	mapping.emplace("AE07", keyboard::scan::Num7);
	mapping.emplace("AE08", keyboard::scan::Num8);
	mapping.emplace("AE09", keyboard::scan::Num9);
	mapping.emplace("AE10", keyboard::scan::Num0);
	mapping.emplace("AE11", keyboard::scan::Hyphen);
	mapping.emplace("AE12", keyboard::scan::Equal);
	mapping.emplace("BKSP", keyboard::scan::Backspace);
	mapping.emplace("TAB", keyboard::scan::Tab);
	mapping.emplace("AD01", keyboard::scan::Q);
	mapping.emplace("AD02", keyboard::scan::W);
	mapping.emplace("AD03", keyboard::scan::E);
	mapping.emplace("AD04", keyboard::scan::R);
	mapping.emplace("AD05", keyboard::scan::T);
	mapping.emplace("AD06", keyboard::scan::Y);
	mapping.emplace("AD07", keyboard::scan::U);
	mapping.emplace("AD08", keyboard::scan::I);
	mapping.emplace("AD09", keyboard::scan::O);
	mapping.emplace("AD10", keyboard::scan::P);
	mapping.emplace("AD11", keyboard::scan::LBracket);
	mapping.emplace("AD12", keyboard::scan::RBracket);
	mapping.emplace("BKSL", keyboard::scan::Backslash);
	mapping.emplace("RTRN", keyboard::scan::Enter);

	mapping.emplace("CAPS", keyboard::scan::CapsLock);
	mapping.emplace("AC01", keyboard::scan::A);
	mapping.emplace("AC02", keyboard::scan::S);
	mapping.emplace("AC03", keyboard::scan::D);
	mapping.emplace("AC04", keyboard::scan::F);
	mapping.emplace("AC05", keyboard::scan::G);
	mapping.emplace("AC06", keyboard::scan::H);
	mapping.emplace("AC07", keyboard::scan::J);
	mapping.emplace("AC08", keyboard::scan::K);
	mapping.emplace("AC09", keyboard::scan::L);
	mapping.emplace("AC10", keyboard::scan::Semicolon);
	mapping.emplace("AC11", keyboard::scan::Apostrophe);
	mapping.emplace("AC12", keyboard::scan::Backslash);

	mapping.emplace("LFSH", keyboard::scan::LShift);
	mapping.emplace("AB01", keyboard::scan::Z);
	mapping.emplace("AB02", keyboard::scan::X);
	mapping.emplace("AB03", keyboard::scan::C);
	mapping.emplace("AB04", keyboard::scan::V);
	mapping.emplace("AB05", keyboard::scan::B);
	mapping.emplace("AB06", keyboard::scan::N);
	mapping.emplace("AB07", keyboard::scan::M);
	mapping.emplace("AB08", keyboard::scan::Comma);
	mapping.emplace("AB09", keyboard::scan::Period);
	mapping.emplace("AB10", keyboard::scan::Slash);
	mapping.emplace("RTSH", keyboard::scan::RShift);

	mapping.emplace("LCTL", keyboard::scan::LControl);
	mapping.emplace("LALT", keyboard::scan::LAlt);
	mapping.emplace("SPCE", keyboard::scan::Space);
	mapping.emplace("RCTL", keyboard::scan::RControl);
	mapping.emplace("RALT", keyboard::scan::RAlt);
	mapping.emplace("LVL3", keyboard::scan::RAlt);
	mapping.emplace("ALGR", keyboard::scan::RAlt);
	mapping.emplace("LWIN", keyboard::scan::LSystem);
	mapping.emplace("RWIN", keyboard::scan::RSystem);

	mapping.emplace("HYPR", keyboard::scan::Application);
	mapping.emplace("EXEC", keyboard::scan::Execute);
	mapping.emplace("MDSW", keyboard::scan::ModeChange);
	mapping.emplace("MENU", keyboard::scan::Menu);
	mapping.emplace("COMP", keyboard::scan::Menu);
	mapping.emplace("SELE", keyboard::scan::Select);

	mapping.emplace("ESC", keyboard::scan::Escape);
	mapping.emplace("FK01", keyboard::scan::F1);
	mapping.emplace("FK02", keyboard::scan::F2);
	mapping.emplace("FK03", keyboard::scan::F3);
	mapping.emplace("FK04", keyboard::scan::F4);
	mapping.emplace("FK05", keyboard::scan::F5);
	mapping.emplace("FK06", keyboard::scan::F6);
	mapping.emplace("FK07", keyboard::scan::F7);
	mapping.emplace("FK08", keyboard::scan::F8);
	mapping.emplace("FK09", keyboard::scan::F9);
	mapping.emplace("FK10", keyboard::scan::F10);
	mapping.emplace("FK11", keyboard::scan::F11);
	mapping.emplace("FK12", keyboard::scan::F12);

	mapping.emplace("PRSC", keyboard::scan::PrintScreen);
	mapping.emplace("SCLK", keyboard::scan::ScrollLock);
	mapping.emplace("PAUS", keyboard::scan::Pause);

	mapping.emplace("INS", keyboard::scan::Insert);
	mapping.emplace("HOME", keyboard::scan::Home);
	mapping.emplace("PGUP", keyboard::scan::PageUp);
	mapping.emplace("DELE", keyboard::scan::Delete);
	mapping.emplace("END", keyboard::scan::End);
	mapping.emplace("PGDN", keyboard::scan::PageDown);

	mapping.emplace("UP", keyboard::scan::Up);
	mapping.emplace("RGHT", keyboard::scan::Right);
	mapping.emplace("DOWN", keyboard::scan::Down);
	mapping.emplace("LEFT", keyboard::scan::Left);

	mapping.emplace("NMLK", keyboard::scan::NumLock);
	mapping.emplace("KPDV", keyboard::scan::NumpadDivide);
	mapping.emplace("KPMU", keyboard::scan::NumpadMultiply);
	mapping.emplace("KPSU", keyboard::scan::NumpadMinus);

	mapping.emplace("KP7", keyboard::scan::Numpad7);
	mapping.emplace("KP8", keyboard::scan::Numpad8);
	mapping.emplace("KP9", keyboard::scan::Numpad9);
	mapping.emplace("KPAD", keyboard::scan::NumpadPlus);
	mapping.emplace("KP4", keyboard::scan::Numpad4);
	mapping.emplace("KP5", keyboard::scan::Numpad5);
	mapping.emplace("KP6", keyboard::scan::Numpad6);
	mapping.emplace("KP1", keyboard::scan::Numpad1);
	mapping.emplace("KP2", keyboard::scan::Numpad2);
	mapping.emplace("KP3", keyboard::scan::Numpad3);
	mapping.emplace("KPEN", keyboard::scan::NumpadEnter);
	mapping.emplace("KP0", keyboard::scan::Numpad0);
	mapping.emplace("KPDL", keyboard::scan::NumpadDecimal);
	mapping.emplace("KPEQ", keyboard::scan::NumpadEqual);

	mapping.emplace("FK13", keyboard::scan::F13);
	mapping.emplace("FK14", keyboard::scan::F14);
	mapping.emplace("FK15", keyboard::scan::F15);
	mapping.emplace("FK16", keyboard::scan::F16);
	mapping.emplace("FK17", keyboard::scan::F17);
	mapping.emplace("FK18", keyboard::scan::F18);
	mapping.emplace("FK19", keyboard::scan::F19);
	mapping.emplace("FK20", keyboard::scan::F20);
	mapping.emplace("FK21", keyboard::scan::F21);
	mapping.emplace("FK22", keyboard::scan::F22);
	mapping.emplace("FK23", keyboard::scan::F23);
	mapping.emplace("FK24", keyboard::scan::F24);
	mapping.emplace("LMTA", keyboard::scan::LSystem);
	mapping.emplace("RMTA", keyboard::scan::RSystem);
	mapping.emplace("MUTE", keyboard::scan::VolumeMute);
	mapping.emplace("VOL-", keyboard::scan::VolumeDown);
	mapping.emplace("VOL+", keyboard::scan::VolumeUp);
	mapping.emplace("STOP", keyboard::scan::Stop);
	mapping.emplace("REDO", keyboard::scan::Redo);
	mapping.emplace("AGAI", keyboard::scan::Redo);
	mapping.emplace("UNDO", keyboard::scan::Undo);
	mapping.emplace("COPY", keyboard::scan::Copy);
	mapping.emplace("PAST", keyboard::scan::Paste);
	mapping.emplace("FIND", keyboard::scan::Search);
	mapping.emplace("CUT", keyboard::scan::Cut);
	mapping.emplace("HELP", keyboard::scan::Help);

	mapping.emplace("I156", keyboard::scan::LaunchApplication1);
	mapping.emplace("I157", keyboard::scan::LaunchApplication2);
	mapping.emplace("I164", keyboard::scan::Favorites);
	mapping.emplace("I166", keyboard::scan::Back);
	mapping.emplace("I167", keyboard::scan::Forward);
	mapping.emplace("I171", keyboard::scan::MediaNextTrack);
	mapping.emplace("I172", keyboard::scan::MediaPlayPause);
	mapping.emplace("I173", keyboard::scan::MediaPreviousTrack);
	mapping.emplace("I174", keyboard::scan::MediaStop);
	mapping.emplace("I180", keyboard::scan::HomePage);
	mapping.emplace("I181", keyboard::scan::Refresh);
	mapping.emplace("I223", keyboard::scan::LaunchMail);
	mapping.emplace("I234", keyboard::scan::LaunchMediaSelect);

	return mapping;
}

////////////////////////////////////////////////////////////
void ensure_mapping()
{
	static bool isMappingInitialized = false;

	if(isMappingInitialized)
		return;

	// Phase 1: Initialize mappings with default values
	for(auto& keycode : scancode_to_keycode_mapping)
		keycode = nullKeyCode;

	for(auto& scancode : key_code_to_scancode_mapping)
		scancode = keyboard::scan::Unknown;

	// Phase 2: Get XKB names with key code
	Display* display = priv::open_display();

	char name[XkbKeyNameLength + 1];
	XkbDescPtr descriptor = XkbGetMap(display, 0, XkbUseCoreKbd);
	XkbGetNames(display, XkbKeyNamesMask, descriptor);

	std::unordered_map<std::string, keyboard::scancode> nameScancodeMap = get_name_scancode_map();
	keyboard::scancode scancode = keyboard::scan::Unknown;

	for(int keycode = descriptor->min_key_code; keycode <= descriptor->max_key_code; ++keycode)
	{
		if(!is_valid_keycode(static_cast<KeyCode>(keycode)))
		{
			continue;
		}

		std::memcpy(name, descriptor->names->keys[keycode].name, XkbKeyNameLength);
		name[XkbKeyNameLength] = '\0';

		auto mappedScancode = nameScancodeMap.find(std::string(name));
		scancode = keyboard::scan::Unknown;

		if(mappedScancode != nameScancodeMap.end())
			scancode = mappedScancode->second;

		if(scancode != keyboard::scan::Unknown)
			scancode_to_keycode_mapping[static_cast<std::size_t>(scancode)] = static_cast<KeyCode>(keycode);

		key_code_to_scancode_mapping[keycode] = scancode;
	}

	XkbFreeNames(descriptor, XkbKeyNamesMask, True);
	XkbFreeKeyboard(descriptor, 0, True);

	// Phase 3: Translate un-translated keycodes using traditional X11 KeySym lookups
	for(int keycode = 8; keycode < maxKeyCode; ++keycode)
	{
		if(key_code_to_scancode_mapping[static_cast<KeyCode>(keycode)] == keyboard::scan::Unknown)
		{
			scancode = translate_keycode(display, static_cast<KeyCode>(keycode));

			if(scancode != keyboard::scan::Unknown &&
			   scancode_to_keycode_mapping[static_cast<std::size_t>(scancode)] == nullKeyCode)
				scancode_to_keycode_mapping[static_cast<std::size_t>(scancode)] =
					static_cast<KeyCode>(keycode);

			key_code_to_scancode_mapping[keycode] = scancode;
		}
	}

	priv::close_display(display);

	isMappingInitialized = true;
}

////////////////////////////////////////////////////////////
KeyCode scancode_to_key_code(keyboard::scancode code)
{
	ensure_mapping();

	if(code != keyboard::scan::Unknown)
		return scancode_to_keycode_mapping[static_cast<std::size_t>(code)];

	return nullKeyCode;
}

////////////////////////////////////////////////////////////
keyboard::scancode key_code_to_scancode(KeyCode code)
{
	ensure_mapping();

	if(is_valid_keycode(code))
		return key_code_to_scancode_mapping[code];

	return keyboard::scan::Unknown;
}

////////////////////////////////////////////////////////////
KeyCode key_to_key_code(keyboard::key key)
{
	KeySym keysym = priv::key_to_key_sym(key);

	if(keysym != NoSymbol)
	{
		Display* display = priv::open_display();
		KeyCode keycode = XKeysymToKeycode(display, keysym);
		priv::close_display(display);

		if(keycode != nullKeyCode)
			return keycode;
	}

	// Fallback for when XKeysymToKeycode cannot tell the KeyCode for XK_Alt_R
	if(key == keyboard::RAlt)
		return scancode_to_keycode_mapping[static_cast<std::size_t>(keyboard::scan::RAlt)];

	return nullKeyCode;
}

////////////////////////////////////////////////////////////
KeySym scancode_to_key_sym(keyboard::scancode code)
{
	Display* display = priv::open_display();

	KeySym keysym = NoSymbol;
	KeyCode keycode = scancode_to_key_code(code);

	if(keycode != nullKeyCode) // ensure that this Scancode is mapped to keycode
		keysym = XkbKeycodeToKeysym(display, keycode, 0, 0);

	priv::close_display(display);

	return keysym;
}

////////////////////////////////////////////////////////////
bool is_key_pressedImpl(KeyCode keycode)
{
	if(keycode != nullKeyCode)
	{
		Display* display = priv::open_display();

		// Get the whole keyboard state
		char keys[32];
		XQueryKeymap(display, keys);

		priv::close_display(display);

		// Check our keycode
		return (keys[keycode / 8] & (1 << (keycode % 8))) != 0;
	}

	return false;
}

} // anonymous namespace

////////////////////////////////////////////////////////////
bool keyboard_impl::is_key_pressed(keyboard::key key)
{
	KeyCode keycode = key_to_key_code(key);
	return is_key_pressedImpl(keycode);
}

////////////////////////////////////////////////////////////
bool keyboard_impl::is_key_pressed(keyboard::scancode code)
{
	KeyCode keycode = scancode_to_key_code(code);
	return is_key_pressedImpl(keycode);
}

////////////////////////////////////////////////////////////
keyboard::scancode keyboard_impl::delocalize(keyboard::key key)
{
	KeyCode keycode = key_to_key_code(key);
	return key_code_to_scancode(keycode);
}

////////////////////////////////////////////////////////////
keyboard::key keyboard_impl::localize(keyboard::scancode code)
{
	KeySym keysym = scancode_to_key_sym(code);
	return key_sym_to_key(keysym);
}

////////////////////////////////////////////////////////////
std::string keyboard_impl::get_description(keyboard::scancode code)
{
	bool checkInput = true;

	// these scancodes actually correspond to keys with input
	// but we want to return their description, not their behaviour
	// clang-format off
	if (code == keyboard::scan::Enter ||
	   code == keyboard::scan::Escape ||
	   code == keyboard::scan::Backspace ||
	   code == keyboard::scan::Tab ||
	   code == keyboard::scan::Space ||
	   code == keyboard::scan::ScrollLock ||
	   code == keyboard::scan::Pause ||
	   code == keyboard::scan::Delete ||
	   code == keyboard::scan::NumpadDivide ||
	   code == keyboard::scan::NumpadMultiply ||
	   code == keyboard::scan::NumpadMinus ||
	   code == keyboard::scan::NumpadPlus ||
	   code == keyboard::scan::NumpadEqual ||
	   code == keyboard::scan::NumpadEnter ||
	   code == keyboard::scan::NumpadDecimal)
	// clang-format on
	{
		checkInput = false;
	}

	if(checkInput)
	{
		KeySym keysym = scancode_to_key_sym(code);
		char32_t unicode = keysym_to_unicode(keysym);

		if(unicode != 0)
		{
			std::vector<uint32_t> unicode_data;
			unicode_data.resize(1);
			utf8::encode(unicode, unicode_data.data());
			std::vector<char> result;
			result.resize(5, 0);
			utf32::to_utf8(unicode_data.begin(), unicode_data.end(), result.data());
			std::string s = result.data();
			return s;
		}
	}

	// Fallback to our best guess for the keys that are known to be independent of the layout.
	// clang-format off
	switch (code)
	{
		case keyboard::scan::Enter:              return "Enter";
		case keyboard::scan::Escape:             return "Escape";
		case keyboard::scan::Backspace:          return "Backspace";
		case keyboard::scan::Tab:                return "Tab";
		case keyboard::scan::Space:              return "Space";

		case keyboard::scan::F1:                 return "F1";
		case keyboard::scan::F2:                 return "F2";
		case keyboard::scan::F3:                 return "F3";
		case keyboard::scan::F4:                 return "F4";
		case keyboard::scan::F5:                 return "F5";
		case keyboard::scan::F6:                 return "F6";
		case keyboard::scan::F7:                 return "F7";
		case keyboard::scan::F8:                 return "F8";
		case keyboard::scan::F9:                 return "F9";
		case keyboard::scan::F10:                return "F10";
		case keyboard::scan::F11:                return "F11";
		case keyboard::scan::F12:                return "F12";
		case keyboard::scan::F13:                return "F13";
		case keyboard::scan::F14:                return "F14";
		case keyboard::scan::F15:                return "F15";
		case keyboard::scan::F16:                return "F16";
		case keyboard::scan::F17:                return "F17";
		case keyboard::scan::F18:                return "F18";
		case keyboard::scan::F19:                return "F19";
		case keyboard::scan::F20:                return "F20";
		case keyboard::scan::F21:                return "F21";
		case keyboard::scan::F22:                return "F22";
		case keyboard::scan::F23:                return "F23";
		case keyboard::scan::F24:                return "F24";

		case keyboard::scan::CapsLock:           return "Caps Lock";
		case keyboard::scan::PrintScreen:        return "Print Screen";
		case keyboard::scan::ScrollLock:         return "Scroll Lock";

		case keyboard::scan::Pause:              return "Pause";
		case keyboard::scan::Insert:             return "Insert";
		case keyboard::scan::Home:               return "Home";
		case keyboard::scan::PageUp:             return "Page Up";
		case keyboard::scan::Delete:             return "Delete";
		case keyboard::scan::End:                return "End";
		case keyboard::scan::PageDown:           return "Page Down";

		case keyboard::scan::Left:               return "Left Arrow";
		case keyboard::scan::Right:              return "Right Arrow";
		case keyboard::scan::Down:               return "Down Arrow";
		case keyboard::scan::Up:                 return "Up Arrow";

		case keyboard::scan::NumLock:            return "Num Lock";
		case keyboard::scan::NumpadDivide:       return "Divide (Numpad)";
		case keyboard::scan::NumpadMultiply:     return "Multiply (Numpad)";
		case keyboard::scan::NumpadMinus:        return "Minus (Numpad)";
		case keyboard::scan::NumpadPlus:         return "Plus (Numpad)";
		case keyboard::scan::NumpadEqual:        return "Equal (Numpad)";
		case keyboard::scan::NumpadEnter:        return "Enter (Numpad)";
		case keyboard::scan::NumpadDecimal:      return "Decimal (Numpad)";

		case keyboard::scan::Numpad0:            return "0 (Numpad)";
		case keyboard::scan::Numpad1:            return "1 (Numpad)";
		case keyboard::scan::Numpad2:            return "2 (Numpad)";
		case keyboard::scan::Numpad3:            return "3 (Numpad)";
		case keyboard::scan::Numpad4:            return "4 (Numpad)";
		case keyboard::scan::Numpad5:            return "5 (Numpad)";
		case keyboard::scan::Numpad6:            return "6 (Numpad)";
		case keyboard::scan::Numpad7:            return "7 (Numpad)";
		case keyboard::scan::Numpad8:            return "8 (Numpad)";
		case keyboard::scan::Numpad9:            return "9 (Numpad)";

		case keyboard::scan::Application:        return "Application";
		case keyboard::scan::Execute:            return "Execute";
		case keyboard::scan::Help:               return "Help";
		case keyboard::scan::Menu:               return "Menu";
		case keyboard::scan::Select:             return "Select";
		case keyboard::scan::Stop:               return "Stop";
		case keyboard::scan::Redo:               return "Redo";
		case keyboard::scan::Undo:               return "Undo";
		case keyboard::scan::Cut:                return "Cut";
		case keyboard::scan::Copy:               return "Copy";
		case keyboard::scan::Paste:              return "Paste";
		case keyboard::scan::Search:             return "Search";

		case keyboard::scan::VolumeMute:         return "Volume Mute";
		case keyboard::scan::VolumeUp:           return "Volume Up";
		case keyboard::scan::VolumeDown:         return "Volume Down";

		case keyboard::scan::LControl:           return "Left Control";
		case keyboard::scan::LShift:             return "Left Shift";
		case keyboard::scan::LAlt:               return "Left Alt";
		case keyboard::scan::LSystem:            return "Left System";
		case keyboard::scan::RControl:           return "Right Control";
		case keyboard::scan::RShift:             return "Right Shift";
		case keyboard::scan::RAlt:               return "Right Alt";
		case keyboard::scan::RSystem:            return "Right System";

		case keyboard::scan::LaunchApplication1: return "Launch Application 1";
		case keyboard::scan::LaunchApplication2: return "Launch Application 2";
		case keyboard::scan::Favorites:          return "Favorites";
		case keyboard::scan::Back:               return "Back";
		case keyboard::scan::Forward:            return "Forward";
		case keyboard::scan::MediaNextTrack:     return "Media Next Track";
		case keyboard::scan::MediaPlayPause:     return "Media Play Pause";
		case keyboard::scan::MediaPreviousTrack: return "Media Previous Track";
		case keyboard::scan::MediaStop:          return "Media Stop";
		case keyboard::scan::HomePage:           return "Home Page";
		case keyboard::scan::Refresh:            return "Refresh";
		case keyboard::scan::LaunchMail:         return "Launch Mail";
		case keyboard::scan::LaunchMediaSelect:  return "Launch Media Select";

		default:                                 return "Unknown Scancode";
	}
	// clang-format on
}

////////////////////////////////////////////////////////////
keyboard::key keyboard_impl::get_key_from_event(XKeyEvent& event)
{
	// Try each KeySym index (modifier group) until we get a match
	for(int i = 0; i < 4; ++i)
	{
		// Get the SFML keyboard code from the keysym of the key that has been pressed
		KeySym keysym = XLookupKeysym(&event, i);
		keyboard::key key = key_sym_to_key(keysym);
		if(key != keyboard::Unknown)
			return key;
	}

	return keyboard::Unknown;
}

////////////////////////////////////////////////////////////
keyboard::scancode keyboard_impl::get_scancode_from_event(XKeyEvent& event)
{
	return key_code_to_scancode(static_cast<KeyCode>(event.keycode));
}

} // namespace priv
} // namespace mml
