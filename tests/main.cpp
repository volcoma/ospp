#include <algorithm>
#include <chrono>
#include <iostream>
#include <ospp/clipboard.h>
#include <ospp/event.h>
#include <ospp/init.h>
#include <ospp/keyboard.h>
#include <ospp/window.h>

#include <thread>

using namespace std::chrono_literals;

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
	auto sz = windows[0].get_size();

	bool full = false;
	bool running = true;
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
					windows.erase(std::remove_if(std::begin(windows), std::end(windows),
												 [id](const auto& window) { return window.get_id() == id; }),
								  std::end(windows));
				}
			}
			if(e.type == os::events::mouse_motion)
			{
//				std::cout << "x1 : " << e.motion.x << std::endl;
//				std::cout << "y1 : " << e.motion.y << std::endl;
//				auto pos = os::mouse::get_position(windows[0]);
//				std::cout << "x2 : " << pos.x << std::endl;
//				std::cout << "y2 : " << pos.y << std::endl;
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

				// std::cout << "pressed : " << std::boolalpha << os::key::is_pressed(e.key.code) <<
				// std::endl;

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

			}
			if(e.type == os::events::key_up)
			{
				std::cout << "key up" << std::endl;
				std::cout << "code : " << os::key::to_string(e.key.code) << std::endl;
				std::cout << "ctrl : " << std::boolalpha << e.key.ctrl << std::endl;
				std::cout << "alt : " << std::boolalpha << e.key.alt << std::endl;
				std::cout << "shift : " << std::boolalpha << e.key.shift << std::endl;
				std::cout << "gui : " << std::boolalpha << e.key.system << std::endl;

				// std::cout << "pressed : " << std::boolalpha << os::key::is_pressed(e.key.code) <<
				// std::endl;
			}
			if(e.type == os::events::text_input)
			{

			}
		}

		// auto pos = os::mouse::get_position();
		// std::cout << "x : " << pos.x << std::endl;
		// std::cout << "y : " << pos.y << std::endl;
		std::this_thread::sleep_for(16ms);
	}
	os::shutdown();
	return 0;
}
