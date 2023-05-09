#ifndef MML_KEY_SYM_TO_KEY_MAPPING_X11_HPP
#define MML_KEY_SYM_TO_KEY_MAPPING_X11_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <X11/Xlib.h> // XKeyEvent
#include <mml/window/keyboard.hpp>

namespace mml
{
namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Convert X11 KeySym to Keyboard::Key
///
/// \param symbol X11 KeySym
///
/// \return The corresponding Keyboard::Key
///
////////////////////////////////////////////////////////////
keyboard::key key_sym_to_key(KeySym symbol);

////////////////////////////////////////////////////////////
/// \brief Convert Keyboard::Key to X11 KeySym
///
/// \param key X11 Keyboard::Key
///
/// \return The corresponding X11 KeySym
///
////////////////////////////////////////////////////////////
KeySym key_to_key_sym(keyboard::key key);

} // namespace priv

} // namespace mml

#endif // MML_INPUTIMPLX11_HPP
