[![Build Status](https://travis-ci.org/volcoma/ospp.svg?branch=master)](https://travis-ci.org/volcoma/ospp)
[![Build status](https://ci.appveyor.com/api/projects/status/ehyrmrsyr49xj06q?svg=true)](https://ci.appveyor.com/project/volcoma/ospp)

## ospp c++14 cross-platform window and input library
- The library is JUST windowing and input.
- Wrapping the most popular windowing libraries under one api
- Supported backends - SDL, GLFW, MML

```c++
int main()
{
	if(!os::init())
	{
		return -1;
	}

	os::window window{"win", os::window::centered, os::window::centered, 500, 500, os::window::resizable};
					  
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
					std::cout << "quit ('q' key pressed)" << std::endl;
					running = false;
					break;
				}
			}
		}

		std::this_thread::sleep_for(16ms);
	}
	
    	return os::shutdown();
}
```
