#include <ospp/event.h>
#include <ospp/init.h>
#include <ospp/window.h>
#include <chrono>
#include <thread>
#include <algorithm>

using namespace std::chrono_literals;
int main()
{
	os::init();

    auto modes = os::display_mode::get_available_modes();
    auto mode = os::display_mode::get_desktop_mode();
    std::vector<os::window> windows = {
        {"win 1", 500, 500, os::window::resizable},
        {"win 2", 500, 500, os::window::resizable}
    };

    auto sz = windows[0].get_size();

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
                    windows.erase(std::remove_if(std::begin(windows), std::end(windows), [id](const auto& window)
                    {
                        return window.get_id() == id;
                    }), std::end(windows));
                }
            }
            if(e.type == os::events::text_input)
            {
                windows[0].request_close();
                int a = 0;
                a++;
            }
        }

		std::this_thread::sleep_for(16ms);
	}
	os::shutdown();
	return 0;
}
