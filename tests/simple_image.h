#include <algorithm>
#include <chrono>
#include <iostream>
#include <ospp/clipboard.h>
#include <ospp/cursor.h>
#include <ospp/event.h>
#include <ospp/init.h>
#include <ospp/keyboard.h>
#include <ospp/window.h>

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

struct simple_image
{
	std::vector<uint8_t> pixels;
	uint32_t w{};
	uint32_t h{};
	int32_t hot_x{};
	int32_t hot_y{};
};

static simple_image parse_image(const uint8_t* data, const uint8_t* mask, int w, int h, int hot_x, int hot_y)
{
	int x, y;
	uint32_t* pixel;
	uint8_t datab = 0, maskb = 0;
	const uint32_t black = 0xFF000000;
	const uint32_t white = 0xFFFFFFFF;
	const uint32_t transparent = 0x00000000;

	/* Make sure the width is a multiple of 8 */
	w = ((w + 7) & ~7);

	simple_image image;
	image.pixels.resize(32 * 32 * 4, 0);
	image.w = w;
	image.h = h;
	image.hot_x = hot_x;
	image.hot_y = hot_y;

	uint32_t pitch = 32 * 4;
	for(y = 0; y < h; ++y)
	{
		pixel = reinterpret_cast<uint32_t*>(image.pixels.data() + y * pitch);
		for(x = 0; x < w; ++x)
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

static simple_image load_cursor_image(const char* image[])
{
	int i, row, col;
	uint8_t data[4 * 32];
	uint8_t mask[4 * 32];
	int hot_x, hot_y;
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

	sscanf(image[4 + row], "%d,%d", &hot_x, &hot_y);
	return parse_image(data, mask, 32, 32, hot_x, hot_y);
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
		std::cout << "-------------------------" << std::endl;
		std::cout << "desktop mode:" << std::endl;
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
		std::vector<os::window> windows = {{"win 1", os::window::centered, os::window::centered, 500, 500}};

		os::start_text_input();

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
		os::cursor cursor_image(image.pixels.data(), {image.w, image.h}, {image.hot_x, image.hot_y});

		while(running)
		{

			os::event e{};
			while(os::poll_event(e))
			{
				if(e.type == os::events::quit)
				{
					running = false;
					break;
				}
				if(e.type == os::events::window)
				{
					if(e.window.type == os::window_event_id::close)
					{
						auto id = e.window.window_id;
						windows.erase(
							std::remove_if(std::begin(windows), std::end(windows),
										   [id](const auto& window) { return window.get_id() == id; }),
							std::end(windows));
					}
				}
				if(e.type == os::events::mouse_motion)
				{
					//					std::cout << "x1 : " << e.motion.x << std::endl;
					//					std::cout << "y1 : " << e.motion.y << std::endl;
					//					auto pos = os::mouse::get_position(windows[0]);
					//					std::cout << "x2 : " << pos.x << std::endl;
					//					std::cout << "y2 : " << pos.y << std::endl;
				}
				if(e.type == os::events::mouse_wheel)
				{
					std::cout << "x : " << e.wheel.x << std::endl;
					std::cout << "y : " << e.wheel.y << std::endl;
				}
				if(e.type == os::events::key_down)
				{
					std::cout << "key down" << std::endl;
					std::cout << "code : " << os::key::to_string(e.key.code) << std::endl;
					std::cout << "ctrl : " << std::boolalpha << e.key.ctrl << std::endl;
					std::cout << "alt : " << std::boolalpha << e.key.alt << std::endl;
					std::cout << "shift : " << std::boolalpha << e.key.shift << std::endl;
					std::cout << "gui : " << std::boolalpha << e.key.system << std::endl;

					std::cout << "pressed : " << std::boolalpha << os::key::is_pressed(e.key.code)
							  << std::endl;

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

					if(e.key.code == os::key::f)
					{
						full = !full;
						windows[0].set_fullscreen(full);
					}
					if(e.key.code == os::key::t)
					{
						windows[0].set_cursor(cursor_arrow);
					}
					if(e.key.code == os::key::y)
					{
						windows[0].set_cursor(cursor_image);
					}
					if(e.key.code == os::key::v)
					{
						show = !show;
						windows[0].show_cursor(show);
					}

					if(e.key.code == os::key::b)
					{
						grab = !grab;
						windows[0].grab_input(grab);
					}
				}
				if(e.type == os::events::key_up)
				{
					std::cout << "key up" << std::endl;
					std::cout << "code : " << os::key::to_string(e.key.code) << std::endl;
					std::cout << "ctrl : " << std::boolalpha << e.key.ctrl << std::endl;
					std::cout << "alt : " << std::boolalpha << e.key.alt << std::endl;
					std::cout << "shift : " << std::boolalpha << e.key.shift << std::endl;
					std::cout << "gui : " << std::boolalpha << e.key.system << std::endl;

					std::cout << "pressed : " << std::boolalpha << os::key::is_pressed(e.key.code)
							  << std::endl;
				}
			}

			// auto pos = os::mouse::get_position();
			// std::cout << "x : " << pos.x << std::endl;
			// std::cout << "y : " << pos.y << std::endl;
			std::this_thread::sleep_for(16ms);
		}
	}

	os::shutdown();
	return 0;
}
