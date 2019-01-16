#include <algorithm>
#include <chrono>
#include <iostream>
#include <ospp/event.h>
#include <ospp/init.h>
#include <ospp/window.h>
#include <ospp/keyboard.h>
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
            if(e.type == os::events::mouse_wheel)
            {
                std::cout << "x : " << e.wheel.x << std::endl;
                std::cout << "y : " << e.wheel.y << std::endl;
            }
            if(e.type == os::events::key_down)
			{
				std::cout << os::key::to_string(e.key.code) << std::endl;
			}
			if(e.type == os::events::text_input)
			{
//				full = !full;
//				windows[0].set_fullscreen(full);
//				int a = 0;
//				a++;
			}
		}

		std::this_thread::sleep_for(16ms);
	}
	os::shutdown();
	return 0;
}
