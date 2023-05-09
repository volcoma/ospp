////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <mml/system/err.hpp>
#include <mml/window/input_impl.hpp>
#include <mml/window/unix/display.hpp>
#include <mml/window/unix/keyboard_impl.hpp>
#include <mml/window/window.hpp>

namespace mml
{
namespace priv
{
////////////////////////////////////////////////////////////
bool input_impl::is_key_pressed(keyboard::key key)
{
	return keyboard_impl::is_key_pressed(key);
}

////////////////////////////////////////////////////////////
bool input_impl::is_key_pressed(keyboard::scancode code)
{
	return keyboard_impl::is_key_pressed(code);
}

////////////////////////////////////////////////////////////
keyboard::key input_impl::localize(keyboard::scancode code)
{
	return keyboard_impl::localize(code);
}

////////////////////////////////////////////////////////////
keyboard::scancode input_impl::delocalize(keyboard::key key)
{
	return keyboard_impl::delocalize(key);
}

////////////////////////////////////////////////////////////
std::string input_impl::get_description(keyboard::scancode code)
{
	return keyboard_impl::get_description(code);
}

////////////////////////////////////////////////////////////
void input_impl::set_virtual_keyboard_visible(bool /*visible*/)
{
	// Not applicable
}

////////////////////////////////////////////////////////////
bool input_impl::is_mouse_button_pressed(mouse::button button)
{
	// Open a connection with the X server
	Display* display = open_display();

	// we don't care about these but they are required
	::Window root, child;
	int wx, wy;
	int gx, gy;

	unsigned int buttons = 0;
	XQueryPointer(display, DefaultRootWindow(display), &root, &child, &gx, &gy, &wx, &wy, &buttons);

	// Close the connection with the X server
	close_display(display);

	switch(button)
	{
		case mouse::left:
			return buttons & Button1Mask;
		case mouse::right:
			return buttons & Button3Mask;
		case mouse::middle:
			return buttons & Button2Mask;
		case mouse::x_button1:
			return false; // not supported by X
		case mouse::x_button2:
			return false; // not supported by X
		default:
			return false;
	}

	return false;
}

////////////////////////////////////////////////////////////
std::array<std::int32_t, 2> input_impl::get_mouse_position()
{
	// Open a connection with the X server
	Display* display = open_display();

	// we don't care about these but they are required
	::Window root, child;
	int x, y;
	unsigned int buttons;

	int gx = 0;
	int gy = 0;
	XQueryPointer(display, DefaultRootWindow(display), &root, &child, &gx, &gy, &x, &y, &buttons);

	// Close the connection with the X server
	close_display(display);

	return std::array<std::int32_t, 2>({{gx, gy}});
}

////////////////////////////////////////////////////////////
std::array<std::int32_t, 2> input_impl::get_mouse_position(const window& relativeTo)
{
	window_handle handle = relativeTo.native_handle();
	if(handle)
	{
		// Open a connection with the X server
		Display* display = open_display();

		// we don't care about these but they are required
		::Window root, child;
		int gx, gy;
		unsigned int buttons;

		int x = 0;
		int y = 0;
		XQueryPointer(display, handle, &root, &child, &gx, &gy, &x, &y, &buttons);

		// Close the connection with the X server
		close_display(display);

		return std::array<std::int32_t, 2>({{x, y}});
	}
	else
	{
		return std::array<std::int32_t, 2>({{0, 0}});
	}
}

////////////////////////////////////////////////////////////
void input_impl::set_mouse_position(const std::array<std::int32_t, 2>& position)
{
	// Open a connection with the X server
	Display* display = open_display();

	XWarpPointer(display, None, DefaultRootWindow(display), 0, 0, 0, 0, position[0], position[1]);
	XFlush(display);

	// Close the connection with the X server
	close_display(display);
}

////////////////////////////////////////////////////////////
void input_impl::set_mouse_position(const std::array<std::int32_t, 2>& position, const window& relativeTo)
{
	// Open a connection with the X server
	Display* display = open_display();

	window_handle handle = relativeTo.native_handle();
	if(handle)
	{
		XWarpPointer(display, None, handle, 0, 0, 0, 0, position[0], position[1]);
		XFlush(display);
	}

	// Close the connection with the X server
	close_display(display);
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
	return std::array<std::int32_t, 2>();
}

////////////////////////////////////////////////////////////
std::array<std::int32_t, 2> input_impl::get_touch_position(unsigned int /*finger*/,
														   const window& /*relativeTo*/)
{
	// Not applicable
	return std::array<std::int32_t, 2>();
}

} // namespace priv

} // namespace mml
