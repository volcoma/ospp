////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <mml/window/keyboard.hpp>
#include <mml/window/input_impl.hpp>


namespace mml
{
////////////////////////////////////////////////////////////
bool keyboard::is_key_pressed(key k)
{
    return priv::input_impl::is_key_pressed(k);
}

bool keyboard::is_key_pressed(scancode code)
{
    return priv::input_impl::is_key_pressed(code);
}

////////////////////////////////////////////////////////////
keyboard::key keyboard::localize(scancode code)
{
    return priv::input_impl::localize(code);
}

////////////////////////////////////////////////////////////
keyboard::scancode keyboard::delocalize(key k)
{
    return priv::input_impl::delocalize(k);
}

////////////////////////////////////////////////////////////
std::string keyboard::get_description(scancode code)
{
    return priv::input_impl::get_description(code);
}

////////////////////////////////////////////////////////////
void keyboard::set_virtual_keyboard_visible(bool visible)
{
    priv::input_impl::set_virtual_keyboard_visible(visible);
}

} // namespace mml
