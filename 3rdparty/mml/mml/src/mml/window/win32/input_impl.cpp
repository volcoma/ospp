////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#ifdef _WIN32_WINDOWS
    #undef _WIN32_WINDOWS
#endif
#ifdef _WIN32_WINNT
    #undef _WIN32_WINNT
#endif
#define _WIN32_WINDOWS 0x0501
#define _WIN32_WINNT   0x0501
#include <mml/window/window.hpp>
#include <mml/window/win32/input_impl.hpp>
#include <mml/system/utf.hpp>
#include <windows.h>


namespace mml
{
namespace priv
{
////////////////////////////////////////////////////////////
keyboard::scancode input_impl::key_to_scancode_mapping_[keyboard::KeyCount]; ///< Mapping from Key to Scancode
keyboard::key      input_impl::scancode_to_key_mapping_[static_cast<std::size_t>(keyboard::scan::ScancodeCount)]; ///< Mapping from Scancode to Key


////////////////////////////////////////////////////////////
keyboard::key virtual_key_to_mml_key(UINT virtualKey)
{
    // clang-format off
    switch (virtualKey)
    {
        case 'A':           return keyboard::A;
        case 'B':           return keyboard::B;
        case 'C':           return keyboard::C;
        case 'D':           return keyboard::D;
        case 'E':           return keyboard::E;
        case 'F':           return keyboard::F;
        case 'G':           return keyboard::G;
        case 'H':           return keyboard::H;
        case 'I':           return keyboard::I;
        case 'J':           return keyboard::J;
        case 'K':           return keyboard::K;
        case 'L':           return keyboard::L;
        case 'M':           return keyboard::M;
        case 'N':           return keyboard::N;
        case 'O':           return keyboard::O;
        case 'P':           return keyboard::P;
        case 'Q':           return keyboard::Q;
        case 'R':           return keyboard::R;
        case 'S':           return keyboard::S;
        case 'T':           return keyboard::T;
        case 'U':           return keyboard::U;
        case 'V':           return keyboard::V;
        case 'W':           return keyboard::W;
        case 'X':           return keyboard::X;
        case 'Y':           return keyboard::Y;
        case 'Z':           return keyboard::Z;
        case '0':           return keyboard::Num0;
        case '1':           return keyboard::Num1;
        case '2':           return keyboard::Num2;
        case '3':           return keyboard::Num3;
        case '4':           return keyboard::Num4;
        case '5':           return keyboard::Num5;
        case '6':           return keyboard::Num6;
        case '7':           return keyboard::Num7;
        case '8':           return keyboard::Num8;
        case '9':           return keyboard::Num9;
        case VK_ESCAPE:     return keyboard::Escape;
        case VK_LCONTROL:   return keyboard::LControl;
        case VK_LSHIFT:     return keyboard::LShift;
        case VK_LMENU:      return keyboard::LAlt;
        case VK_LWIN:       return keyboard::LSystem;
        case VK_RCONTROL:   return keyboard::RControl;
        case VK_RSHIFT:     return keyboard::RShift;
        case VK_RMENU:      return keyboard::RAlt;
        case VK_RWIN:       return keyboard::RSystem;
        case VK_APPS:       return keyboard::Menu;
        case VK_OEM_4:      return keyboard::LBracket;
        case VK_OEM_6:      return keyboard::RBracket;
        case VK_OEM_1:      return keyboard::Semicolon;
        case VK_OEM_COMMA:  return keyboard::Comma;
        case VK_OEM_PERIOD: return keyboard::Period;
        case VK_OEM_7:      return keyboard::Apostrophe;
        case VK_OEM_2:      return keyboard::Slash;
        case VK_OEM_5:      return keyboard::Backslash;
        case VK_OEM_3:      return keyboard::Grave;
        case VK_OEM_PLUS:   return keyboard::Equal;
        case VK_OEM_MINUS:  return keyboard::Hyphen;
        case VK_SPACE:      return keyboard::Space;
        case VK_RETURN:     return keyboard::Enter;
        case VK_BACK:       return keyboard::Backspace;
        case VK_TAB:        return keyboard::Tab;
        case VK_PRIOR:      return keyboard::PageUp;
        case VK_NEXT:       return keyboard::PageDown;
        case VK_END:        return keyboard::End;
        case VK_HOME:       return keyboard::Home;
        case VK_INSERT:     return keyboard::Insert;
        case VK_DELETE:     return keyboard::Delete;
        case VK_ADD:        return keyboard::Add;
        case VK_SUBTRACT:   return keyboard::Subtract;
        case VK_MULTIPLY:   return keyboard::Multiply;
        case VK_DIVIDE:     return keyboard::Divide;
        case VK_LEFT:       return keyboard::Left;
        case VK_RIGHT:      return keyboard::Right;
        case VK_UP:         return keyboard::Up;
        case VK_DOWN:       return keyboard::Down;
        case VK_NUMPAD0:    return keyboard::Numpad0;
        case VK_NUMPAD1:    return keyboard::Numpad1;
        case VK_NUMPAD2:    return keyboard::Numpad2;
        case VK_NUMPAD3:    return keyboard::Numpad3;
        case VK_NUMPAD4:    return keyboard::Numpad4;
        case VK_NUMPAD5:    return keyboard::Numpad5;
        case VK_NUMPAD6:    return keyboard::Numpad6;
        case VK_NUMPAD7:    return keyboard::Numpad7;
        case VK_NUMPAD8:    return keyboard::Numpad8;
        case VK_NUMPAD9:    return keyboard::Numpad9;
        case VK_F1:         return keyboard::F1;
        case VK_F2:         return keyboard::F2;
        case VK_F3:         return keyboard::F3;
        case VK_F4:         return keyboard::F4;
        case VK_F5:         return keyboard::F5;
        case VK_F6:         return keyboard::F6;
        case VK_F7:         return keyboard::F7;
        case VK_F8:         return keyboard::F8;
        case VK_F9:         return keyboard::F9;
        case VK_F10:        return keyboard::F10;
        case VK_F11:        return keyboard::F11;
        case VK_F12:        return keyboard::F12;
        case VK_F13:        return keyboard::F13;
        case VK_F14:        return keyboard::F14;
        case VK_F15:        return keyboard::F15;
        case VK_PAUSE:      return keyboard::Pause;
        default:            return keyboard::Unknown;
    }
    // clang-format on
}

////////////////////////////////////////////////////////////
int mml_key_to_virtual_key(keyboard::key key)
{
    // clang-format off
    switch (key)
    {
        case keyboard::A:          return 'A';
        case keyboard::B:          return 'B';
        case keyboard::C:          return 'C';
        case keyboard::D:          return 'D';
        case keyboard::E:          return 'E';
        case keyboard::F:          return 'F';
        case keyboard::G:          return 'G';
        case keyboard::H:          return 'H';
        case keyboard::I:          return 'I';
        case keyboard::J:          return 'J';
        case keyboard::K:          return 'K';
        case keyboard::L:          return 'L';
        case keyboard::M:          return 'M';
        case keyboard::N:          return 'N';
        case keyboard::O:          return 'O';
        case keyboard::P:          return 'P';
        case keyboard::Q:          return 'Q';
        case keyboard::R:          return 'R';
        case keyboard::S:          return 'S';
        case keyboard::T:          return 'T';
        case keyboard::U:          return 'U';
        case keyboard::V:          return 'V';
        case keyboard::W:          return 'W';
        case keyboard::X:          return 'X';
        case keyboard::Y:          return 'Y';
        case keyboard::Z:          return 'Z';
        case keyboard::Num0:       return '0';
        case keyboard::Num1:       return '1';
        case keyboard::Num2:       return '2';
        case keyboard::Num3:       return '3';
        case keyboard::Num4:       return '4';
        case keyboard::Num5:       return '5';
        case keyboard::Num6:       return '6';
        case keyboard::Num7:       return '7';
        case keyboard::Num8:       return '8';
        case keyboard::Num9:       return '9';
        case keyboard::Escape:     return VK_ESCAPE;
        case keyboard::LControl:   return VK_LCONTROL;
        case keyboard::LShift:     return VK_LSHIFT;
        case keyboard::LAlt:       return VK_LMENU;
        case keyboard::LSystem:    return VK_LWIN;
        case keyboard::RControl:   return VK_RCONTROL;
        case keyboard::RShift:     return VK_RSHIFT;
        case keyboard::RAlt:       return VK_RMENU;
        case keyboard::RSystem:    return VK_RWIN;
        case keyboard::Menu:       return VK_APPS;
        case keyboard::LBracket:   return VK_OEM_4;
        case keyboard::RBracket:   return VK_OEM_6;
        case keyboard::Semicolon:  return VK_OEM_1;
        case keyboard::Comma:      return VK_OEM_COMMA;
        case keyboard::Period:     return VK_OEM_PERIOD;
        case keyboard::Apostrophe: return VK_OEM_7;
        case keyboard::Slash:      return VK_OEM_2;
        case keyboard::Backslash:  return VK_OEM_5;
        case keyboard::Grave:      return VK_OEM_3;
        case keyboard::Equal:      return VK_OEM_PLUS;
        case keyboard::Hyphen:     return VK_OEM_MINUS;
        case keyboard::Space:      return VK_SPACE;
        case keyboard::Enter:      return VK_RETURN;
        case keyboard::Backspace:  return VK_BACK;
        case keyboard::Tab:        return VK_TAB;
        case keyboard::PageUp:     return VK_PRIOR;
        case keyboard::PageDown:   return VK_NEXT;
        case keyboard::End:        return VK_END;
        case keyboard::Home:       return VK_HOME;
        case keyboard::Insert:     return VK_INSERT;
        case keyboard::Delete:     return VK_DELETE;
        case keyboard::Add:        return VK_ADD;
        case keyboard::Subtract:   return VK_SUBTRACT;
        case keyboard::Multiply:   return VK_MULTIPLY;
        case keyboard::Divide:     return VK_DIVIDE;
        case keyboard::Left:       return VK_LEFT;
        case keyboard::Right:      return VK_RIGHT;
        case keyboard::Up:         return VK_UP;
        case keyboard::Down:       return VK_DOWN;
        case keyboard::Numpad0:    return VK_NUMPAD0;
        case keyboard::Numpad1:    return VK_NUMPAD1;
        case keyboard::Numpad2:    return VK_NUMPAD2;
        case keyboard::Numpad3:    return VK_NUMPAD3;
        case keyboard::Numpad4:    return VK_NUMPAD4;
        case keyboard::Numpad5:    return VK_NUMPAD5;
        case keyboard::Numpad6:    return VK_NUMPAD6;
        case keyboard::Numpad7:    return VK_NUMPAD7;
        case keyboard::Numpad8:    return VK_NUMPAD8;
        case keyboard::Numpad9:    return VK_NUMPAD9;
        case keyboard::F1:         return VK_F1;
        case keyboard::F2:         return VK_F2;
        case keyboard::F3:         return VK_F3;
        case keyboard::F4:         return VK_F4;
        case keyboard::F5:         return VK_F5;
        case keyboard::F6:         return VK_F6;
        case keyboard::F7:         return VK_F7;
        case keyboard::F8:         return VK_F8;
        case keyboard::F9:         return VK_F9;
        case keyboard::F10:        return VK_F10;
        case keyboard::F11:        return VK_F11;
        case keyboard::F12:        return VK_F12;
        case keyboard::F13:        return VK_F13;
        case keyboard::F14:        return VK_F14;
        case keyboard::F15:        return VK_F15;
        case keyboard::Pause:      return VK_PAUSE;
        default:                   return 0;
    }
    // clang-format on
}

////////////////////////////////////////////////////////////
WORD mml_scan_to_win_scan(keyboard::scancode code)
{
    // Convert an SFML scancode to a Windows scancode
    // Reference: https://msdn.microsoft.com/en-us/library/aa299374(v=vs.60).aspx
    // clang-format off
    switch (code)
    {
        case keyboard::scan::A: return 0x1E;
        case keyboard::scan::B: return 0x30;
        case keyboard::scan::C: return 0x2E;
        case keyboard::scan::D: return 0x20;
        case keyboard::scan::E: return 0x12;
        case keyboard::scan::F: return 0x21;
        case keyboard::scan::G: return 0x22;
        case keyboard::scan::H: return 0x23;
        case keyboard::scan::I: return 0x17;
        case keyboard::scan::J: return 0x24;
        case keyboard::scan::K: return 0x25;
        case keyboard::scan::L: return 0x26;
        case keyboard::scan::M: return 0x32;
        case keyboard::scan::N: return 0x31;
        case keyboard::scan::O: return 0x18;
        case keyboard::scan::P: return 0x19;
        case keyboard::scan::Q: return 0x10;
        case keyboard::scan::R: return 0x13;
        case keyboard::scan::S: return 0x1F;
        case keyboard::scan::T: return 0x14;
        case keyboard::scan::U: return 0x16;
        case keyboard::scan::V: return 0x2F;
        case keyboard::scan::W: return 0x11;
        case keyboard::scan::X: return 0x2D;
        case keyboard::scan::Y: return 0x15;
        case keyboard::scan::Z: return 0x2C;

        case keyboard::scan::Num1: return 0x02;
        case keyboard::scan::Num2: return 0x03;
        case keyboard::scan::Num3: return 0x04;
        case keyboard::scan::Num4: return 0x05;
        case keyboard::scan::Num5: return 0x06;
        case keyboard::scan::Num6: return 0x07;
        case keyboard::scan::Num7: return 0x08;
        case keyboard::scan::Num8: return 0x09;
        case keyboard::scan::Num9: return 0x0A;
        case keyboard::scan::Num0: return 0x0B;

        case keyboard::scan::Enter:      return 0x1C;
        case keyboard::scan::Escape:     return 0x01;
        case keyboard::scan::Backspace:  return 0x0E;
        case keyboard::scan::Tab:        return 0x0F;
        case keyboard::scan::Space:      return 0x39;
        case keyboard::scan::Hyphen:     return 0x0C;
        case keyboard::scan::Equal:      return 0x0D;
        case keyboard::scan::LBracket:   return 0x1A;
        case keyboard::scan::RBracket:   return 0x1B;
        case keyboard::scan::Backslash:  return 0x2B;
        case keyboard::scan::Semicolon:  return 0x27;
        case keyboard::scan::Apostrophe: return 0x28;
        case keyboard::scan::Grave:      return 0x29;
        case keyboard::scan::Comma:      return 0x33;
        case keyboard::scan::Period:     return 0x34;
        case keyboard::scan::Slash:      return 0x35;

        case keyboard::scan::F1:  return 0x3B;
        case keyboard::scan::F2:  return 0x3C;
        case keyboard::scan::F3:  return 0x3D;
        case keyboard::scan::F4:  return 0x3E;
        case keyboard::scan::F5:  return 0x3F;
        case keyboard::scan::F6:  return 0x40;
        case keyboard::scan::F7:  return 0x41;
        case keyboard::scan::F8:  return 0x42;
        case keyboard::scan::F9:  return 0x43;
        case keyboard::scan::F10: return 0x44;
        case keyboard::scan::F11: return 0x57;
        case keyboard::scan::F12: return 0x58;
        case keyboard::scan::F13: return 0x64;
        case keyboard::scan::F14: return 0x65;
        case keyboard::scan::F15: return 0x66;
        case keyboard::scan::F16: return 0x67;
        case keyboard::scan::F17: return 0x68;
        case keyboard::scan::F18: return 0x69;
        case keyboard::scan::F19: return 0x6A;
        case keyboard::scan::F20: return 0x6B;
        case keyboard::scan::F21: return 0x6C;
        case keyboard::scan::F22: return 0x6D;
        case keyboard::scan::F23: return 0x6E;
        case keyboard::scan::F24: return 0x76;

        case keyboard::scan::CapsLock:    return 0x3A;
        case keyboard::scan::PrintScreen: return 0xE037;
        case keyboard::scan::ScrollLock:  return 0x46;
        case keyboard::scan::Pause:       return 0x45;
        case keyboard::scan::Insert:      return 0xE052;
        case keyboard::scan::Home:        return 0xE047;
        case keyboard::scan::PageUp:      return 0xE049;
        case keyboard::scan::Delete:      return 0xE053;
        case keyboard::scan::End:         return 0xE04F;
        case keyboard::scan::PageDown:    return 0xE051;
        case keyboard::scan::Right:       return 0xE04D;
        case keyboard::scan::Left:        return 0xE04B;
        case keyboard::scan::Down:        return 0xE050;
        case keyboard::scan::Up:          return 0xE048;
        case keyboard::scan::NumLock:     return 0xE045;

        case keyboard::scan::NumpadDivide:   return 0xE035;
        case keyboard::scan::NumpadMultiply: return 0x37;
        case keyboard::scan::NumpadMinus:    return 0x4A;
        case keyboard::scan::NumpadPlus:     return 0x4E;
        case keyboard::scan::NumpadEqual:    return 0x7E;
        case keyboard::scan::NumpadEnter:    return 0xE01C;
        case keyboard::scan::NumpadDecimal:  return 0x53;

        case keyboard::scan::Numpad1:        return 0x4F;
        case keyboard::scan::Numpad2:        return 0x50;
        case keyboard::scan::Numpad3:        return 0x51;
        case keyboard::scan::Numpad4:        return 0x4B;
        case keyboard::scan::Numpad5:        return 0x4C;
        case keyboard::scan::Numpad6:        return 0x4D;
        case keyboard::scan::Numpad7:        return 0x47;
        case keyboard::scan::Numpad8:        return 0x48;
        case keyboard::scan::Numpad9:        return 0x49;
        case keyboard::scan::Numpad0:        return 0x52;

        case keyboard::scan::NonUsBackslash: return 0x56;
        // No known scancode for keyboard::scan::Application
        // No known scancode for keyboard::scan::Execute
        // No known scancode for keyboard::scan::ModeChange
        case keyboard::scan::Help:           return 0xE061;
        case keyboard::scan::Menu:           return 0xE05D;
        case keyboard::scan::Select:         return 0xE01E;
        // No known scancode for keyboard::scan::Redo
        // No known scancode for keyboard::scan::Undo
        // No known scancode for keyboard::scan::Cut
        // No known scancode for keyboard::scan::Copy
        // No known scancode for keyboard::scan::Paste

        case keyboard::scan::VolumeMute:         return 0xE020;
        case keyboard::scan::VolumeUp:           return 0xE02E;
        case keyboard::scan::VolumeDown:         return 0xE02C;
        case keyboard::scan::MediaPlayPause:     return 0xE022;
        case keyboard::scan::MediaStop:          return 0xE024;
        case keyboard::scan::MediaNextTrack:     return 0xE019;
        case keyboard::scan::MediaPreviousTrack: return 0xE010;

        case keyboard::scan::LControl: return 0x1D;
        case keyboard::scan::LShift:   return 0x2A;
        case keyboard::scan::LAlt:     return 0x38;
        case keyboard::scan::LSystem:  return 0xE05B;
        case keyboard::scan::RControl: return 0xE01D;
        case keyboard::scan::RShift:   return 0x36;
        case keyboard::scan::RAlt:     return 0xE038;
        case keyboard::scan::RSystem:  return 0xE05C;

        case keyboard::scan::Back:      return 0xE06A;
        case keyboard::scan::Forward:   return 0xE069;
        case keyboard::scan::Refresh:   return 0xE067;
        case keyboard::scan::Stop:      return 0xE068;
        case keyboard::scan::Search:    return 0xE065;
        case keyboard::scan::Favorites: return 0xE066;
        case keyboard::scan::HomePage:  return 0xE030;

        case keyboard::scan::LaunchApplication1: return 0xE06B;
        case keyboard::scan::LaunchApplication2: return 0xE021;
        case keyboard::scan::LaunchMail:         return 0xE06C;
        case keyboard::scan::LaunchMediaSelect:  return 0xE06D;

        // Unable to map to a scancode
        default: return 0x0;
    }
    // clang-format on
}

////////////////////////////////////////////////////////////
WORD mml_scan_to_win_scan_extended(keyboard::scancode code)
{
    // Convert an SFML scancode to a Windows scancode
    // Reference: https://msdn.microsoft.com/en-us/library/aa299374(v=vs.60).aspx
    // clang-format off
    switch (code)
    {
        case keyboard::scan::PrintScreen:        return 55  | 0xE100;
        case keyboard::scan::Insert:             return 82  | 0xE100;
        case keyboard::scan::Home:               return 71  | 0xE100;
        case keyboard::scan::PageUp:             return 73  | 0xE100;
        case keyboard::scan::Delete:             return 83  | 0xE100;
        case keyboard::scan::End:                return 79  | 0xE100;
        case keyboard::scan::PageDown:           return 81  | 0xE100;
        case keyboard::scan::Right:              return 77  | 0xE100;
        case keyboard::scan::Left:               return 75  | 0xE100;
        case keyboard::scan::Down:               return 80  | 0xE100;
        case keyboard::scan::Up:                 return 72  | 0xE100;
        case keyboard::scan::NumLock:            return 69  | 0xE100;
        case keyboard::scan::NumpadEnter:        return 28  | 0xE100;
        case keyboard::scan::NumpadDivide:       return 53  | 0xE100;
        case keyboard::scan::Help:               return 97  | 0xE100;
        case keyboard::scan::Menu:               return 93  | 0xE100;
        case keyboard::scan::Select:             return 30  | 0xE100;
        case keyboard::scan::VolumeMute:         return 32  | 0xE100;
        case keyboard::scan::VolumeUp:           return 46  | 0xE100;
        case keyboard::scan::VolumeDown:         return 44  | 0xE100;
        case keyboard::scan::MediaPlayPause:     return 34  | 0xE100;
        case keyboard::scan::MediaStop:          return 36  | 0xE100;
        case keyboard::scan::MediaNextTrack:     return 25  | 0xE100;
        case keyboard::scan::MediaPreviousTrack: return 16  | 0xE100;
        case keyboard::scan::LSystem:            return 91  | 0xE100;
        case keyboard::scan::RControl:           return 29  | 0xE100;
        case keyboard::scan::RAlt:               return 56  | 0xE100;
        case keyboard::scan::RSystem:            return 92  | 0xE100;
        case keyboard::scan::Back:               return 106 | 0xE100;
        case keyboard::scan::Forward:            return 105 | 0xE100;
        case keyboard::scan::Refresh:            return 103 | 0xE100;
        case keyboard::scan::Stop:               return 104 | 0xE100;
        case keyboard::scan::Search:             return 101 | 0xE100;
        case keyboard::scan::Favorites:          return 102 | 0xE100;
        case keyboard::scan::HomePage:           return 48  | 0xE100;
        case keyboard::scan::LaunchApplication1: return 107 | 0xE100;
        case keyboard::scan::LaunchApplication2: return 33  | 0xE100;
        case keyboard::scan::LaunchMail:         return 108 | 0xE100;
        case keyboard::scan::LaunchMediaSelect:  return 109 | 0xE100;

        // Use non-extended mapping
        default: return mml_scan_to_win_scan(code);
    }
    // clang-format on
}

UINT mml_scan_to_virtual_key(keyboard::scancode code)
{
    const WORD winScancode = mml_scan_to_win_scan(code);

    // Manually map non-extended key codes
    // clang-format off
    switch (code)
    {
        case keyboard::scan::Numpad0:       return VK_NUMPAD0;
        case keyboard::scan::Numpad1:       return VK_NUMPAD1;
        case keyboard::scan::Numpad2:       return VK_NUMPAD2;
        case keyboard::scan::Numpad3:       return VK_NUMPAD3;
        case keyboard::scan::Numpad4:       return VK_NUMPAD4;
        case keyboard::scan::Numpad5:       return VK_NUMPAD5;
        case keyboard::scan::Numpad6:       return VK_NUMPAD6;
        case keyboard::scan::Numpad7:       return VK_NUMPAD7;
        case keyboard::scan::Numpad8:       return VK_NUMPAD8;
        case keyboard::scan::Numpad9:       return VK_NUMPAD9;
        case keyboard::scan::NumpadMinus:   return VK_SUBTRACT;
        case keyboard::scan::NumpadDecimal: return VK_DECIMAL;
        case keyboard::scan::NumpadDivide:  return VK_DIVIDE;
        case keyboard::scan::Pause:         return VK_PAUSE;
        case keyboard::scan::RControl:      return VK_RCONTROL;
        case keyboard::scan::RAlt:          return VK_RMENU;
        default:                            return MapVirtualKey(winScancode, MAPVK_VSC_TO_VK_EX);
    }
    // clang-format on
}

bool is_valid_scancode(keyboard::scancode code)
{
    return code > keyboard::scan::Unknown && code < keyboard::scan::ScancodeCount;
}

bool is_valid_key(keyboard::key key)
{
    return key > keyboard::Unknown && key < keyboard::KeyCount;
}

////////////////////////////////////////////////////////////
void input_impl::ensure_mappings()
{
    static bool isMappingInitialized = false;

    if (isMappingInitialized)
        return;

    // Phase 1: Initialize mappings with default values
    for (auto& scancode : key_to_scancode_mapping_)
        scancode = keyboard::scan::Unknown;

    for (auto& key : scancode_to_key_mapping_)
        key = keyboard::Unknown;

    // Phase 2: Translate scancode to virtual code to key names
    for (int i = 0; i < static_cast<int>(keyboard::scan::ScancodeCount); ++i)
    {
        const auto          scan       = static_cast<keyboard::scancode>(i);
        const UINT          virtualKey = mml_scan_to_virtual_key(scan);
        const keyboard::key key        = virtual_key_to_mml_key(virtualKey);
        if (key != keyboard::Unknown && key_to_scancode_mapping_[key] == keyboard::scan::Unknown)
            key_to_scancode_mapping_[key] = scan;
        scancode_to_key_mapping_[static_cast<std::size_t>(scan)] = key;
    }

    isMappingInitialized = true;
}

////////////////////////////////////////////////////////////
bool input_impl::is_key_pressed(keyboard::key key)
{
    const int virtualKey = mml_key_to_virtual_key(key);
    return (GetAsyncKeyState(virtualKey) & 0x8000) != 0;
}

////////////////////////////////////////////////////////////
bool input_impl::is_key_pressed(keyboard::scancode code)
{
    const UINT virtualKey = mml_scan_to_virtual_key(code);
    return (GetAsyncKeyState(static_cast<int>(virtualKey)) & KF_UP) != 0;
}

////////////////////////////////////////////////////////////
keyboard::key input_impl::localize(keyboard::scancode code)
{
    if (!is_valid_scancode(code))
        return keyboard::Unknown;

    ensure_mappings();

    return scancode_to_key_mapping_[static_cast<std::size_t>(code)];
}

////////////////////////////////////////////////////////////
keyboard::scancode input_impl::delocalize(keyboard::key key)
{
    if (!is_valid_key(key))
        return keyboard::scan::Unknown;

    ensure_mappings();

    return key_to_scancode_mapping_[key];
}

////////////////////////////////////////////////////////////
std::string input_impl::get_description(keyboard::scancode code)
{
    const WORD winCode = mml_scan_to_win_scan_extended(code);
    const int  bufSize = 1024;
    WCHAR      name[bufSize];
    const int  result = GetKeyNameText(winCode << 16, name, bufSize);
    if (result > 0)
    {
        std::string message;
		std::size_t length = std::wcslen(name);
		if (length > 0)
		{
			message.reserve(length + 1);
			utf8::from_wide(name, name + length, std::back_inserter(message));
		}
        return message;
    }
    return "Unknown";
}


////////////////////////////////////////////////////////////
void input_impl::set_virtual_keyboard_visible(bool visible)
{
    // Not applicable
}


////////////////////////////////////////////////////////////
bool input_impl::is_mouse_button_pressed(mouse::button button)
{
    int vkey = 0;
    switch (button)
    {
        case mouse::left:     vkey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_RBUTTON : VK_LBUTTON; break;
        case mouse::right:    vkey = GetSystemMetrics(SM_SWAPBUTTON) ? VK_LBUTTON : VK_RBUTTON; break;
        case mouse::middle:   vkey = VK_MBUTTON;  break;
        case mouse::x_button1: vkey = VK_XBUTTON1; break;
        case mouse::x_button2: vkey = VK_XBUTTON2; break;
        default:              vkey = 0;           break;
    }

    return (GetAsyncKeyState(vkey) & 0x8000) != 0;
}


////////////////////////////////////////////////////////////
std::array<std::int32_t, 2> input_impl::get_mouse_position()
{
    POINT point;
    GetCursorPos(&point);
	return std::array<std::int32_t, 2>({ point.x, point.y });
}


////////////////////////////////////////////////////////////
std::array<std::int32_t, 2> input_impl::get_mouse_position(const window& relativeTo)
{
    window_handle handle = relativeTo.native_handle();
    if (handle)
    {
        POINT point;
        GetCursorPos(&point);
        ScreenToClient(handle, &point);
		return std::array<std::int32_t, 2>({ point.x, point.y });
    }
    else
    {
		return std::array<std::int32_t, 2>({ 0, 0 });
    }
}


////////////////////////////////////////////////////////////
void input_impl::set_mouse_position(const std::array<std::int32_t, 2>& position)
{
    SetCursorPos(position[0], position[1]);
}


////////////////////////////////////////////////////////////
void input_impl::set_mouse_position(const std::array<std::int32_t, 2>& position, const window& relativeTo)
{
    window_handle handle = relativeTo.native_handle();
    if (handle)
    {
        POINT point = {position[0], position[1]};
        ClientToScreen(handle, &point);
        SetCursorPos(point.x, point.y);
    }
}


////////////////////////////////////////////////////////////
bool input_impl::is_touch_down(unsigned int /*finger*/)
{
    // Not applicable
    return false;
}


////////////////////////////////////////////////////////////
std::array<std::int32_t, 2> input_impl::get_touch_position(unsigned int /*finger*/)
{
    // Not applicable
	return std::array<std::int32_t, 2>({ 0, 0 });
}


////////////////////////////////////////////////////////////
std::array<std::int32_t, 2> input_impl::get_touch_position(unsigned int /*finger*/, const window& /*relativeTo*/)
{
    // Not applicable
	return std::array<std::int32_t, 2>({ 0, 0 });
}

} // namespace priv

} // namespace mml
