#pragma once

#include "../../window.h"

#include "error.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <algorithm>

namespace os
{
namespace detail
{
namespace glfw
{

inline auto create_impl(const std::string& title, uint32_t width, uint32_t height, uint32_t flags)
	-> GLFWwindow*
{
	GLFWmonitor* monitor = nullptr;
	if(flags & window::fullscreen)
	{
		monitor = glfwGetPrimaryMonitor();
	}
	if(flags & window::fullscreen_desktop)
	{
		monitor = glfwGetPrimaryMonitor();
		auto mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	}
	if(flags & window::hidden)
	{
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	}
	if(flags & window::borderless)
	{
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	}
	if(flags & window::resizable)
	{
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	}
	if(flags & window::minimized)
	{
	}
	if(flags & window::maximized)
	{
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	}

	auto window =
		glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), monitor, nullptr);

	glfwDefaultWindowHints();

	return window;
}

struct window_deleter
{
	void operator()(GLFWwindow* window) const noexcept
	{
		glfwDestroyWindow(window);
	}
};


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
    windows.erase(std::remove_if(std::begin(windows), std::end(windows), [id](const auto& win)
    {
        return win->get_id() == id;
    }), std::end(windows));
}

using on_window_create = void (*)(GLFWwindow *);
inline on_window_create& on_win_create()
{
    static on_window_create callback = nullptr;
    return callback;
}

struct window_impl
{

public:
	window_impl(const std::string& title, uint32_t width, uint32_t height, uint32_t flags)
        : impl_(create_impl(title, width, height, flags))
	{
		if(impl_ == nullptr)
		{
			OS_GLFW_ERROR_HANDLER_VOID();
		}

        id_ = register_window(this);

        glfwSetWindowUserPointer(impl_.get(), this);

        auto callback = on_win_create();
        if(callback)
        {
            callback(impl_.get());
        }
	}

    ~window_impl()
    {
        unregister_window(id_);
    }

    auto get_impl() -> GLFWwindow*
    {
        return impl_.get();
    }

	auto get_native_handle() const -> native_handle
	{
		return {};
	}
	auto get_native_display() const -> native_display
	{
		return {};
	}

	auto is_open() const noexcept -> bool
	{
		return impl_ != nullptr;
	}

	auto get_id() const noexcept -> uint32_t
	{
		return id_;
	}

	auto get_brightness() const noexcept -> float
	{
		return 1.0f;
	}

	void set_brightness(float bright)
	{
	}

	void set_size(const area& size) noexcept
	{
		glfwSetWindowSize(impl_.get(), static_cast<int>(size.w), static_cast<int>(size.h));
	}

	auto get_size() const noexcept -> area
	{
		area result{};
		int w{};
		int h{};
		glfwGetWindowSize(impl_.get(), &w, &h);
		result.w = static_cast<uint32_t>(w);
		result.h = static_cast<uint32_t>(h);
		return result;
	}

	void set_maximum_size(const area& size) noexcept
	{
		max_size_ = size;
		glfwSetWindowSizeLimits(impl_.get(), GLFW_DONT_CARE, GLFW_DONT_CARE, static_cast<int>(size.w),
								static_cast<int>(size.h));
	}

	auto get_maximum_size() const noexcept -> area
	{
		return max_size_;
	}

	void set_minimum_size(const area& size) noexcept
	{
		min_size_ = size;
		glfwSetWindowSizeLimits(impl_.get(), static_cast<int>(size.w), static_cast<int>(size.h),
								GLFW_DONT_CARE, GLFW_DONT_CARE);
	}

	auto get_minimum_size() const noexcept -> area
	{
		return min_size_;
	}

	void set_position(const point& pos) noexcept
	{
		glfwSetWindowPos(impl_.get(), static_cast<int>(pos.x), static_cast<int>(pos.y));
	}

	auto get_position() noexcept -> point
	{
		point result;
		int x{};
		int y{};
		glfwGetWindowPos(impl_.get(), &x, &y);
		result.x = static_cast<int32_t>(x);
		result.y = static_cast<int32_t>(y);
		return result;
	}

	auto get_title() const noexcept -> std::string
	{
		return {};
	}

	void set_title(const std::string& str) noexcept
	{
		glfwSetWindowTitle(impl_.get(), str.c_str());
	}

	void show() noexcept
	{
		glfwShowWindow(impl_.get());
	}

	void hide() noexcept
	{
		glfwHideWindow(impl_.get());
	}

	void maximize() noexcept
	{
		glfwMaximizeWindow(impl_.get());
	}

	void minimize() noexcept
	{
	}

	void restore() noexcept
	{
		glfwRestoreWindow(impl_.get());
	}

	void raise() noexcept
	{
	}

	void set_border(bool b) noexcept
	{
	}

	void set_fullscreen(bool b)
	{
		//        auto monitor = glfwGetPrimaryMonitor();
		//        auto mode = glfwGetVideoMode(monitor);

		//        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		//        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		//        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		//        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		//		glfwSetWindowMonitor(impl_.get(), monitor, 0, 0, mode->width, mode->height,
		//mode->refreshRate);
	}

	void set_opacity(float opacity)
	{
		glfwSetWindowOpacity(impl_.get(), opacity);
	}

	auto get_opacity() const -> float
	{
		return glfwGetWindowOpacity(impl_.get());
	}

	void grab_input(bool b) noexcept
	{
		glfwSetInputMode(impl_.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	bool is_input_grabbed() const noexcept
	{
		return glfwGetInputMode(impl_.get(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
	}

	void request_focus()
	{
		glfwFocusWindow(impl_.get());
	}

	void set_mouse_position(const point& pos) noexcept
	{
		glfwSetCursorPos(impl_.get(), static_cast<double>(pos.x), static_cast<double>(pos.y));
	}

    auto get_mouse_position() const
    {
        point result;
        double x{};
        double y{};
        glfwGetCursorPos(impl_.get(), &x, &y);
        result.x = static_cast<int32_t>(x);
        result.y = static_cast<int32_t>(y);
        return result;
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
    uint32_t id_{};
	area min_size_{};
	area max_size_{};
	std::unique_ptr<GLFWwindow, window_deleter> impl_;
    bool recieved_close_event_{false};
};
}
}
}