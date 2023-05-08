#ifndef MML_INPUTIMPLWIN32_HPP
#define MML_INPUTIMPLWIN32_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <mml/window/keyboard.hpp>
#include <mml/window/mouse.hpp>


namespace mml
{
namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Windows implementation of inputs (keyboard + mouse)
///
////////////////////////////////////////////////////////////
class input_impl
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Check if a key is pressed
    ///
    /// \param key key to check
    ///
    /// \return True if the key is pressed, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool is_key_pressed(keyboard::key key);

    ////////////////////////////////////////////////////////////
    /// \copydoc sf::Keyboard::isKeyPressed(Scancode)
    ///
    ////////////////////////////////////////////////////////////
    static bool is_key_pressed(keyboard::scancode code);

    ////////////////////////////////////////////////////////////
    /// \copydoc sf::Keyboard::localize
    ///
    ////////////////////////////////////////////////////////////
    static keyboard::key localize(keyboard::scancode code);

    ////////////////////////////////////////////////////////////
    /// \copydoc sf::Keyboard::delocalize
    ///
    ////////////////////////////////////////////////////////////
    static keyboard::scancode delocalize(keyboard::key key);

    ////////////////////////////////////////////////////////////
    /// \copydoc sf::Keyboard::getDescription
    ///
    ////////////////////////////////////////////////////////////
    static std::string get_description(keyboard::scancode code);

    ////////////////////////////////////////////////////////////
    /// \brief Show or hide the virtual keyboard
    ///
    /// \param visible True to show, false to hide
    ///
    ////////////////////////////////////////////////////////////
    static void set_virtual_keyboard_visible(bool visible);

    ////////////////////////////////////////////////////////////
    /// \brief Check if a mouse button is pressed
    ///
    /// \param button button to check
    ///
    /// \return True if the button is pressed, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool is_mouse_button_pressed(mouse::button button);

    ////////////////////////////////////////////////////////////
    /// \brief Get the current position of the mouse in desktop coordinates
    ///
    /// This function returns the current position of the mouse
    /// cursor, in global (desktop) coordinates.
    ///
    /// \return Current position of the mouse
    ///
    ////////////////////////////////////////////////////////////
    static std::array<std::int32_t, 2> get_mouse_position();

    ////////////////////////////////////////////////////////////
    /// \brief Get the current position of the mouse in window coordinates
    ///
    /// This function returns the current position of the mouse
    /// cursor, relative to the given window.
    /// If no window is used, it returns desktop coordinates.
    ///
    /// \param relativeTo Reference window
    ///
    /// \return Current position of the mouse
    ///
    ////////////////////////////////////////////////////////////
    static std::array<std::int32_t, 2> get_mouse_position(const window& relativeTo);

    ////////////////////////////////////////////////////////////
    /// \brief Set the current position of the mouse in desktop coordinates
    ///
    /// This function sets the current position of the mouse
    /// cursor in global (desktop) coordinates.
    /// If no window is used, it sets the position in desktop coordinates.
    ///
    /// \param position New position of the mouse
    ///
    ////////////////////////////////////////////////////////////
    static void set_mouse_position(const std::array<std::int32_t, 2>& position);

    ////////////////////////////////////////////////////////////
    /// \brief Set the current position of the mouse in window coordinates
    ///
    /// This function sets the current position of the mouse
    /// cursor, relative to the given window.
    /// If no window is used, it sets the position in desktop coordinates.
    ///
    /// \param position New position of the mouse
    /// \param relativeTo Reference window
    ///
    ////////////////////////////////////////////////////////////
    static void set_mouse_position(const std::array<std::int32_t, 2>& position, const window& relativeTo);

    ////////////////////////////////////////////////////////////
    /// \brief Check if a touch event is currently down
    ///
    /// \param finger Finger index
    ///
    /// \return True if \a finger is currently touching the screen, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool is_touch_down(unsigned int finger);

    ////////////////////////////////////////////////////////////
    /// \brief Get the current position of a touch in desktop coordinates
    ///
    /// This function returns the current touch position
    /// in global (desktop) coordinates.
    ///
    /// \param finger Finger index
    ///
    /// \return Current position of \a finger, or undefined if it's not down
    ///
    ////////////////////////////////////////////////////////////
    static std::array<std::int32_t, 2> get_touch_position(unsigned int finger);

    ////////////////////////////////////////////////////////////
    /// \brief Get the current position of a touch in window coordinates
    ///
    /// This function returns the current touch position
    /// in global (desktop) coordinates.
    ///
    /// \param finger Finger index
    /// \param relativeTo Reference window
    ///
    /// \return Current position of \a finger, or undefined if it's not down
    ///
    ////////////////////////////////////////////////////////////
    static std::array<std::int32_t, 2> get_touch_position(unsigned int finger, const window& relativeTo);

private:
    ////////////////////////////////////////////////////////////
    /// Ensure the mappings are generated from/to Key and Scancode.
    ///
    ////////////////////////////////////////////////////////////
    static void ensure_mappings();

    // NOLINTBEGIN(readability-identifier-naming)
    static keyboard::scancode key_to_scancode_mapping_[keyboard::KeyCount]; ///< Mapping from Key to Scancode
    static keyboard::key scancode_to_key_mapping_[static_cast<std::size_t>(keyboard::scan::ScancodeCount)]; ///< Mapping from Scancode to Key
    // NOLINTEND(readability-identifier-naming)
};

} // namespace priv

} // namespace mml


#endif // MML_INPUTIMPLWIN32_HPP
