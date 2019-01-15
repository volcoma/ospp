#include <algorithm>
#include <chrono>
#include <ospp/event.h>
#include <ospp/init.h>
#include <ospp/window.h>
#include <thread>

using namespace std::chrono_literals;
int main()
{
	os::init();

	auto modes = os::display_mode::get_available_modes();
	auto mode = os::display_mode::get_desktop_mode();
	std::vector<os::window> windows = {{"win 1", os::window::centered, os::window::centered, 500, 500}};

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
			if(e.type == os::events::text_input)
			{
				full = !full;
				windows[0].set_fullscreen(full);
				int a = 0;
				a++;
			}
		}

		std::this_thread::sleep_for(16ms);
	}
	os::shutdown();
	return 0;
}
