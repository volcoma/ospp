[![Build Status](https://travis-ci.org/volcoma/ospp.svg?branch=master)](https://travis-ci.org/volcoma/ospp)
[![Build status](https://ci.appveyor.com/api/projects/status/ehyrmrsyr49xj06q?svg=true)](https://ci.appveyor.com/project/volcoma/ospp)

## osspp c++14 cross-platform window and input library
- The library is JUST windowing and input.
- Wrapping the most popular windowing libraries under one api
- Supported backends - SDL, GLFW, MML

```c++
int main()
{
	os::init();

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
					  
	bool running = true;

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

			if(e.type == os::events::key_down)
			{
				if(e.key.code == os::key::q)
				{
					std::cout << "quit (all windows were closed)" << std::endl;
					running = false;
					break;
				}
			}
		}

		std::this_thread::sleep_for(16ms);
	}

	os::shutdown();
    return 0;
}
```
