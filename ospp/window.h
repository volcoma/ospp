#pragma once
#include "display_mode.h"
#include "types.hpp"
#include <cstdint>
#include <memory>
#include <string>

namespace os
{
using native_handle = void*;
using native_display = void*;

struct window
{
public:
	enum : uint32_t
	{
		fullscreen = 1 << 0,
		fullscreen_desktop = 1 << 1,
		hidden = 1 << 2,
		borderless = 1 << 3,
		resizable = 1 << 4,
		minimized = 1 << 5,
		maximized = 1 << 6,
	};

	window(const std::string& title, const display_mode& display, uint32_t flags);
	window(const std::string& title, uint32_t width, uint32_t height, uint32_t flags);

    auto get_native_handle() const -> native_handle;
    auto get_native_display() const -> native_display;

	auto is_open() const noexcept -> bool;
	auto get_id() const noexcept -> uint32_t;

	auto get_brightness() const noexcept -> float;
	void set_brightness(float bright);

	void set_size(uint32_t width, uint32_t height) noexcept;
	void set_size(const area& size) noexcept;
	auto get_size() const noexcept -> area;

	void set_maximum_size(uint32_t width, uint32_t height) noexcept;
	void set_maximum_size(const area& size) noexcept;
	auto get_maximum_size() const noexcept -> area;

	void set_minimum_size(uint32_t width, uint32_t height) noexcept;
	void set_minimum_size(const area& size) noexcept;
	auto get_minimum_size() const noexcept -> area;

	void set_position(int32_t x, int32_t y) noexcept;
	void set_position(const point& pos) noexcept;
	auto get_position() noexcept -> point;

	auto get_title() const noexcept -> std::string;
	void set_title(const std::string& str) noexcept;

	void show() noexcept;
	void hide() noexcept;

	void maximize() noexcept;
	void minimize() noexcept;
	void restore() noexcept;
	void raise() noexcept;

	void set_border(bool b = true) noexcept;
	void set_fullscreen(bool b = true);

	void set_opacity(float opacity);
	auto get_opacity() const -> float;

	void grab_input(bool b = true) noexcept;
	auto is_input_grabbed() const noexcept -> bool;

	void set_mouse_position(int32_t x, int32_t y) noexcept;
	void set_mouse_position(const point& pos) noexcept;

    void request_focus();
	void request_close() noexcept;

private:
	std::shared_ptr<void> impl_;
};
} // sdl
