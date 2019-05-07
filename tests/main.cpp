#include <algorithm>
#include <chrono>
#include <iostream>
#include <ospp/os.h>

#include <thread>

using namespace std::chrono_literals;

// clang-format off
static const char *arrow[] =
{
    /* width height num_colors chars_per_pixel */
    "    32    32        3            1",
    /* colors */
    "X c #000000",
    ". c #ffffff",
    "  c None",
    /* pixels */
    "X                               ",
    "XX                              ",
    "X.X                             ",
    "X..X                            ",
    "X...X                           ",
    "X....X                          ",
    "X.....X                         ",
    "X......X                        ",
    "X.......X                       ",
    "X........X                      ",
    "X.....XXXXX                     ",
    "X..X..X                         ",
    "X.X X..X                        ",
    "XX  X..X                        ",
    "X    X..X                       ",
    "     X..X                       ",
    "      X..X                      ",
    "      X..X                      ",
    "       XX                       ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "                                ",
    "0,0"
};
// clang-format on

static os::image parse_image(const uint8_t* data, const uint8_t* mask, int w, int h)
{
	uint8_t datab = 0, maskb = 0;
	const uint32_t black = 0xFF000000;
	const uint32_t white = 0xFFFFFFFF;
	const uint32_t transparent = 0x00000000;

	/* Make sure the width is a multiple of 8 */
	w = ((w + 7) & ~7);

	os::image image;
	image.pixels.resize(32 * 32 * 4, 0);
	image.size.w = static_cast<uint32_t>(w);
	image.size.h = static_cast<uint32_t>(h);

	uint32_t pitch = 32 * 4;
	for(int y = 0; y < h; ++y)
	{
		auto pixel = reinterpret_cast<uint32_t*>(image.pixels.data() + y * pitch);
		for(int x = 0; x < w; ++x)
		{
			if((x % 8) == 0)
			{
				datab = *data++;
				maskb = *mask++;
			}
			if(maskb & 0x80)
			{
				*pixel++ = (datab & 0x80) ? black : white;
			}
			else
			{
				*pixel++ = (datab & 0x80) ? black : transparent;
			}
			datab <<= 1;
			maskb <<= 1;
		}
	}

	return image;
}

static os::image load_cursor_image(const char* image[])
{
	int i, row, col;
	uint8_t data[4 * 32];
	uint8_t mask[4 * 32];
	i = -1;
	for(row = 0; row < 32; ++row)
	{
		for(col = 0; col < 32; ++col)
		{
			if(col % 8)
			{
				data[i] <<= 1;
				mask[i] <<= 1;
			}
			else
			{
				++i;
				data[i] = mask[i] = 0;
			}
			switch(image[4 + row][col])
			{
				case 'X':
					data[i] |= 0x01;
					mask[i] |= 0x01;
					break;
				case '.':
					mask[i] |= 0x01;
					break;
				case ' ':
					break;
			}
		}
	}

	return parse_image(data, mask, 32, 32);
}

void print(const os::display_mode& mode)
{
	std::cout << "w : " << mode.w << std::endl;
	std::cout << "h : " << mode.h << std::endl;
	std::cout << "bpp : " << mode.bpp << std::endl;
	std::cout << "refresh rate : " << mode.refresh_rate << std::endl;
}

int main()
{
	os::init();

	{
		auto desktop_mode = os::display_mode::get_desktop_mode();
		std::cout << "desktop mode:" << std::endl;
		std::cout << "-------------------------" << std::endl;
		print(desktop_mode);
		std::cout << "-------------------------" << std::endl;

		auto modes = os::display_mode::get_available_modes();
		std::cout << "available modes:" << std::endl;
		for(const auto& mode : modes)
		{
			std::cout << "-------------------------" << std::endl;
			print(mode);
		}
		std::cout << "-------------------------" << std::endl;
		os::window window{"win 1", os::window::centered, os::window::centered, 500,
						  500,	 os::window::resizable};

		bool full = false;
		bool show = true;
		bool grab = false;

		bool running = true;

		for(const auto& str : {"a", "b", "c", "d", "e"})
		{
			auto key_code = os::key::from_string(str);
			auto key_str = os::key::to_string(key_code);

			std::cout << "key from_string : " << key_str << std::endl;
		}
		os::cursor cursor_arrow(os::cursor::arrow);
		os::cursor cursor_ibeam(os::cursor::ibeam);
		auto image = load_cursor_image(arrow);
		os::cursor cursor_image(image);

		while(running)
		{

			os::event e{};
			while(os::poll_event(e))
			{
				if(e.type == os::events::quit)
				{
					std::cout << "quit (all windows were closed)" << std::endl;
					running = false;
					break;
				}
				if(e.type == os::events::window)
				{
					if(e.window.type == os::window_event_id::close)
					{
						std::cout << "window close" << std::endl;
					}
				}
				if(e.type == os::events::mouse_motion)
				{
					if(os::key::is_pressed(os::key::lshift))
					{
						std::cout << "[event] x : " << e.motion.x << std::endl;
						std::cout << "[event] y : " << e.motion.y << std::endl;
						auto pos = os::mouse::get_position(window);
						std::cout << "[poll] x : " << pos.x << std::endl;
						std::cout << "[poll] y : " << pos.y << std::endl;
					}
				}
				if(e.type == os::events::mouse_wheel)
				{
					std::cout << "x : " << e.wheel.x << std::endl;
					std::cout << "y : " << e.wheel.y << std::endl;
				}
				if(e.type == os::events::key_up)
				{
					std::cout << "key up" << std::endl;
					std::cout << "[event] state : " << std::boolalpha << false << std::endl;
					std::cout << "[poll] state : " << std::boolalpha << os::key::is_pressed(e.key.code)
							  << std::endl;

					std::cout << "code : " << os::key::to_string(e.key.code) << std::endl;
					std::cout << "ctrl : " << std::boolalpha << e.key.ctrl << std::endl;
					std::cout << "alt : " << std::boolalpha << e.key.alt << std::endl;
					std::cout << "shift : " << std::boolalpha << e.key.shift << std::endl;
					std::cout << "gui : " << std::boolalpha << e.key.system << std::endl;
				}
				if(e.type == os::events::key_down)
				{
					std::cout << "key down" << std::endl;
					std::cout << "[event] state : " << std::boolalpha << true << std::endl;
					std::cout << "[poll] state : " << std::boolalpha << os::key::is_pressed(e.key.code)
							  << std::endl;

					std::cout << "code : " << os::key::to_string(e.key.code) << std::endl;
					std::cout << "ctrl : " << std::boolalpha << e.key.ctrl << std::endl;
					std::cout << "alt : " << std::boolalpha << e.key.alt << std::endl;
					std::cout << "shift : " << std::boolalpha << e.key.shift << std::endl;
					std::cout << "gui : " << std::boolalpha << e.key.system << std::endl;

					std::cout << "keyboard state check pressed : " << std::boolalpha
							  << os::key::is_pressed(e.key.code) << std::endl;

					if(e.key.code == os::key::k)
					{
						std::cout << "screen keyboard : " << std::boolalpha << os::has_screen_keyboard()
								  << std::endl;
					}
					if(e.key.code == os::key::g)
					{
						auto text = os::clipboard::get_text();
						std::cout << "clipboard text : " << text << std::endl;
					}

					if(e.key.code == os::key::digit1)
					{
						full = !full;
						window.set_fullscreen(full);
					}
					if(e.key.code == os::key::digit2)
					{
						window.set_cursor(cursor_arrow);
					}
					if(e.key.code == os::key::digit3)
					{
						window.set_cursor(cursor_image);
					}
					if(e.key.code == os::key::digit4)
					{
						show = !show;
						window.show_cursor(show);
					}

					if(e.key.code == os::key::digit5)
					{
						grab = !grab;
						window.grab_input(grab);
					}

					if(e.key.code == os::key::digit6)
					{
						window.set_icon(image);
					}
				}
			}

			std::this_thread::sleep_for(16ms);
		}
	}

	os::shutdown();
	return 0;
}
