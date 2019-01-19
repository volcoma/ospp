#pragma once
#include "cursor.h"
#include "display_mode.h"
#include "types.hpp"
#include <cstdint>
#include <limits>
#include <memory>
#include <string>

namespace os
{
using native_handle = void*;
using native_display = void*;

class window
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
	constexpr static const auto centered = std::numeric_limits<int32_t>::max();

	window(const std::string& title, const display_mode& display, uint32_t flags = 0);
	window(const std::string& title, int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t flags = 0);
	window(const std::string& title, const point& pos, const area& size, uint32_t flags = 0);

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

	void request_focus();
	void request_close() noexcept;

	void set_cursor(const cursor& c) noexcept;
	void show_cursor(bool show) noexcept;

	auto get_impl() const noexcept -> void*;

private:
	std::shared_ptr<void> impl_;
};
} // sdl
