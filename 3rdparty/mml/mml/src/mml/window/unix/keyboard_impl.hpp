#ifndef MML_KEYBOARDIMPLX11_HPP
#define MML_KEYBOARDIMPLX11_HPP

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
/// \brief Linux (X11) implementation of inputs (keyboard + mouse)
///
////////////////////////////////////////////////////////////
class keyboard_impl
{
public:
	////////////////////////////////////////////////////////////
	/// \copydoc keyboard::is_key_pressed(Key)
	///
	////////////////////////////////////////////////////////////
	static bool is_key_pressed(keyboard::key key);

	////////////////////////////////////////////////////////////
	/// \copydoc keyboard::is_key_pressed(Scancode)
	///
	////////////////////////////////////////////////////////////
	static bool is_key_pressed(keyboard::scancode code);

	////////////////////////////////////////////////////////////
	/// \copydoc keyboard::localize
	///
	////////////////////////////////////////////////////////////
	static keyboard::scancode delocalize(keyboard::key key);

	////////////////////////////////////////////////////////////
	/// \copydoc keyboard::delocalize
	///
	////////////////////////////////////////////////////////////
	static keyboard::key localize(keyboard::scancode code);

	////////////////////////////////////////////////////////////
	/// \copydoc keyboard::get_description
	///
	////////////////////////////////////////////////////////////
	static std::string get_description(keyboard::scancode code);

	////////////////////////////////////////////////////////////
	/// \brief Get the keyboard::key from XKeyEvent
	///
	/// \param event Event from which key is gotten
	///
	/// \return A key being pressed or released
	///
	////////////////////////////////////////////////////////////
	static keyboard::key get_key_from_event(XKeyEvent& event);

	////////////////////////////////////////////////////////////
	/// \brief Get the keyboard::scancode from XKeyEvent
	///
	/// \param event Event from which scancode is gotten
	///
	/// \return A scancode of a key being pressed or released
	///
	////////////////////////////////////////////////////////////
	static keyboard::scancode get_scancode_from_event(XKeyEvent& event);
};

} // namespace priv

} // namespace mml

#endif // MML_INPUTIMPLX11_HPP