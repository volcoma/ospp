#pragma once
#include "mouse.h"
#include <chrono>
#include <cstdint>
#include <string>
namespace os
{

// using finger = SDL_Finger;
// using keyboard_event = SDL_KeyboardEvent;
// using mouse_wheel_event = SDL_MouseWheelEvent;
// using touch_finger_event = SDL_TouchFingerEvent;

enum class window_event_id : uint32_t
{
	none = 0,
	shown,
	hidden,
	exposed,
	moved,
	resized,
	size_changed,
	minimized,
	maximized,
	restored,
	enter,
	leave,
	focus_gained,
	focus_lost,
	close
};

enum class events : uint32_t
{
	unkwnown = 0,
	quit,
	app_terminating,
	app_low_memory,
	app_will_enter_background,
	app_did_enter_background,
	app_will_enter_foreground,
	app_did_enter_foreground,

	window,
	key_down,
	key_up,

	text_input,

	mouse_wheel,

	mouse_button,
	mouse_motion,

	finger_down,
	finger_up,
	finger_motion,

	clipboard_update,
	drop_file
};

struct quit_event
{
};

struct window_event
{
	uint32_t window_id{};
	window_event_id type{};
	int32_t data1{};
	int32_t data2{};
};

struct drop_event
{
	uint32_t window_id{};
	std::string file{};
};

struct text_input_event
{
	uint32_t window_id{};
	std::string text_utf8{}; /**< The input text */
};

struct mouse_button_event
{
	uint32_t window_id{};
	mouse::button button{};		 /**< The mouse button index */
	mouse::button_state state{}; /**< ::pressed or ::released */
	int32_t x{};				 /**< X coordinate, relative to window */
	int32_t y{};				 /**< Y coordinate, relative to window */
};

struct mouse_motion_event
{
	uint32_t window_id{};
	int32_t x{}; /**< X coordinate, relative to window */
	int32_t y{}; /**< Y coordinate, relative to window */
};

struct event
{
    drop_event drop{};
    text_input_event text{};
    mouse_button_event button{};
    window_event window{};
    mouse_motion_event motion{};

    events type{};

    quit_event quit{};
};

void push_event(const event& e);

bool poll_event(event& e) noexcept;

} // sdl