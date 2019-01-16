#pragma once

#include "../../window.h"

#include "config.hpp"

#include <algorithm>
#include <cstdint>
#include <map>
#include <memory>
#include <string>

namespace os
{
namespace detail
{
namespace mml
{

inline auto get_impl_flags(uint32_t flags) -> uint32_t
{
	uint32_t result = ::mml::style::titlebar | ::mml::style::close;
	if(flags & window::fullscreen)
	{
		result |= ::mml::style::fullscreen;
	}
	if(flags & window::fullscreen_desktop)
	{
		result |= ::mml::style::fullscreen;
	}
	if(flags & window::hidden)
	{
	}
	if(flags & window::borderless)
	{
	}
	if(flags & window::resizable)
	{
		result |= ::mml::style::resize;
	}
	if(flags & window::minimized)
	{
	}
	if(flags & window::maximized)
	{
	}

	return result;
}

class window_impl;

inline auto get_windows() noexcept -> std::vector<window_impl*>&
{
	static std::vector<window_impl*> windows;
	return windows;
}

inline uint32_t register_window(window_impl* impl)
{
	static uint32_t id{0};
	auto& windows = get_windows();
	windows.emplace_back(impl);
	return ++id;
}

inline void unregister_window(uint32_t id)
{
	auto& windows = get_windows();
	windows.erase(std::remove_if(std::begin(windows), std::end(windows),
								 [id](const auto& win) { return win->get_id() == id; }),
				  std::end(windows));
}

class window_impl
{

public:
	window_impl(const std::string& title, const point& pos, const area& size, uint32_t flags)
		: impl_(::mml::video_mode(size.w, size.h), title, get_impl_flags(flags))
		, title_(title)
	{
		id_ = register_window(this);
		set_position(pos);
	}

	~window_impl()
	{
		unregister_window(id_);
	}

	auto get_impl() -> ::mml::window&
	{
		return impl_;
	}

	auto get_native_handle() const -> native_handle
	{
		return (void*)(uintptr_t)impl_.native_handle();
	}
	auto get_native_display() const -> native_display
	{
		return impl_.native_display_handle();
	}

	auto is_open() const noexcept -> bool
	{
		return impl_.is_open();
	}

	auto get_id() const noexcept -> uint32_t
	{
		return id_;
	}

	auto get_brightness() const noexcept -> float
	{
		return 1.0f;
	}

	void set_brightness(float)
	{
	}

	void set_size(const area& size) noexcept
	{
		impl_.set_size({size.w, size.h});
	}

	auto get_size() const noexcept -> area
	{
		area result{};
		auto size = impl_.get_size();
		result.w = static_cast<uint32_t>(size[0]);
		result.h = static_cast<uint32_t>(size[1]);
		return result;
	}

	void set_maximum_size(const area&) noexcept
	{
	}

	auto get_maximum_size() const noexcept -> area
	{
		return {};
	}

	void set_minimum_size(const area&) noexcept
	{
	}

	auto get_minimum_size() const noexcept -> area
	{
		return {};
	}

	void set_position(const point& pos) noexcept
	{
		if(pos.x == window::centered && pos.y == window::centered)
		{
			auto desktop = display_mode::get_desktop_mode();
			auto sz = get_size();
			impl_.set_position({int32_t(desktop.w / 2 - sz.w / 2), int32_t(desktop.h / 2 - sz.h / 2)});
		}
		else
		{
			impl_.set_position({pos.x, pos.y});
		}
	}

	auto get_position() noexcept -> point
	{
		point result;
		auto pos = impl_.get_position();
		result.x = static_cast<int32_t>(pos[0]);
		result.y = static_cast<int32_t>(pos[1]);
		return result;
	}

	auto get_title() const noexcept -> std::string
	{
		return title_;
	}

	void set_title(const std::string& str) noexcept
	{
		title_ = str;
		impl_.set_title(str);
	}

	void show() noexcept
	{
		impl_.set_visible(true);
	}

	void hide() noexcept
	{
		impl_.set_visible(false);
	}

	void maximize() noexcept
	{
		impl_.maximize();
	}

	void minimize() noexcept
	{
		impl_.minimize();
	}

	void restore() noexcept
	{
		impl_.restore();
	}

	void raise() noexcept
	{
	}

	void set_border(bool) noexcept
	{
	}

	void set_fullscreen(bool)
	{
	}

	void set_opacity(float opacity)
	{
		opacity_ = opacity;
		impl_.set_opacity(opacity);
	}

	auto get_opacity() const -> float
	{
		return opacity_;
	}

	void grab_input(bool b) noexcept
	{
		grabbed_ = b;
		impl_.set_mouse_cursor_grabbed(b);
	}

	bool is_input_grabbed() const noexcept
	{
		return grabbed_;
	}

	void request_focus()
	{
		impl_.request_focus();
	}

	void set_mouse_position(const point& pos) noexcept
	{
		::mml::mouse::set_position({pos.x, pos.y}, impl_);
	}

	void set_recieved_close_event(bool b) noexcept
	{
		recieved_close_event_ = b;
	}
	auto recieved_close_event() const noexcept -> bool
	{
		return recieved_close_event_;
	}

private:
	::mml::window impl_;
	std::string title_{};
	uint32_t id_{0};
	float opacity_{1.0f};
	bool grabbed_{false};
	bool recieved_close_event_{false};
};
}
}
}
