#pragma once

#include "../../window.h"

#include "cursor.hpp"
#include "error.hpp"

#include <cstdint>
#include <memory>
#include <string>

namespace os
{
namespace detail
{
namespace sdl
{
inline auto to_cursor_impl(const cursor& c) -> const cursor_impl&
{
	return *reinterpret_cast<cursor_impl*>(c.get_impl());
}

inline auto get_native_window_handle(const SDL_SysWMinfo& wmi) noexcept -> native_handle
{
	(void)wmi;
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
	return wmi.info.win.window;
#elif defined(SDL_VIDEO_DRIVER_WINRT)
	return wmi.info.winrt.window;
#elif defined(SDL_VIDEO_DRIVER_X11)
	return (void*)(uintptr_t)wmi.info.x11.window;
#elif defined(SDL_VIDEO_DRIVER_DIRECTFB)
	return wmi.info.dfb.window;
#elif defined(SDL_VIDEO_DRIVER_COCOA)
	return wmi.info.cocoa.window;
#elif defined(SDL_VIDEO_DRIVER_UIKIT)
	return wmi.info.uikit.window;
#elif defined(SDL_VIDEO_DRIVER_WAYLAND)
	return wmi.info.wl.surface;
#elif defined(SDL_VIDEO_DRIVER_ANDROID)
	return wmi.info.android.window;
#elif defined(SDL_VIDEO_DRIVER_VIVANTE)
	return (void*)(uintptr_t)wmi.info.vivante.window;
#else
	return nullptr;
#endif
}

inline auto get_native_display_handle(const SDL_SysWMinfo& wmi) noexcept -> native_display
{
	(void)wmi;
#if defined(SDL_VIDEO_DRIVER_WINDOWS)
    return wmi.info.win.hdc;
#elif defined(SDL_VIDEO_DRIVER_WINRT)
	return nullptr;
#elif defined(SDL_VIDEO_DRIVER_X11)
	return wmi.info.x11.display;
#elif defined(SDL_VIDEO_DRIVER_DIRECTFB)
	return nullptr;
#elif defined(SDL_VIDEO_DRIVER_COCOA)
	return nullptr;
#elif defined(SDL_VIDEO_DRIVER_UIKIT)
	return nullptr;
#elif defined(SDL_VIDEO_DRIVER_WAYLAND)
	return wmi.info.wl.display;
#elif defined(SDL_VIDEO_DRIVER_ANDROID)
	return nullptr;
#elif defined(SDL_VIDEO_DRIVER_VIVANTE)
	return (void*)(uintptr_t)wmi.info.vivante.display;
#else
	return nullptr;
#endif
}

inline auto get_impl_flags(uint32_t flags) -> uint32_t
{
	uint32_t result = SDL_WINDOW_ALLOW_HIGHDPI;
	if(flags & window::fullscreen)
	{
		result |= SDL_WINDOW_FULLSCREEN;
	}
	if(flags & window::fullscreen_desktop)
	{
		result |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if(flags & window::hidden)
	{
		result |= SDL_WINDOW_HIDDEN;
	}
	if(flags & window::borderless)
	{
		result |= SDL_WINDOW_BORDERLESS;
	}
	if(flags & window::resizable)
	{
		result |= SDL_WINDOW_RESIZABLE;
	}
	if(flags & window::minimized)
	{
		result |= SDL_WINDOW_MINIMIZED;
	}
	if(flags & window::maximized)
	{
		result |= SDL_WINDOW_MAXIMIZED;
	}

	return result;
}

struct window_deleter
{
	void operator()(SDL_Window* window) const noexcept
	{
		SDL_DestroyWindow(window);
	}
};

class window_impl
{
	constexpr static const auto npos = SDL_WINDOWPOS_UNDEFINED;
	constexpr static const auto centered = SDL_WINDOWPOS_CENTERED;

public:
	window_impl(const std::string& title, const point& pos, const area& size, uint32_t flags)
		: impl_(SDL_CreateWindow(title.c_str(), pos.x == window::centered ? centered : pos.x,
								 pos.y == window::centered ? centered : pos.y, static_cast<int>(size.w),
								 static_cast<int>(size.h), get_impl_flags(flags)))
	{
		if(impl_ == nullptr)
		{
			OS_SDL_ERROR_HANDLER_VOID();
		}
	}

	auto get_impl() const noexcept -> SDL_Window*
	{
		return impl_.get();
	}

	auto get_native_handle() const -> native_handle
	{
		SDL_SysWMinfo wmi;
		SDL_VERSION(&wmi.version);
		if(!SDL_GetWindowWMInfo(impl_.get(), &wmi))
		{
			OS_SDL_ERROR_HANDLER({});
		}

		return get_native_window_handle(wmi);
	}
	auto get_native_display() const -> native_display
	{
		SDL_SysWMinfo wmi;
		SDL_VERSION(&wmi.version);
		if(!SDL_GetWindowWMInfo(impl_.get(), &wmi))
		{
			OS_SDL_ERROR_HANDLER({});
		}
		return get_native_display_handle(wmi);
	}

	auto is_open() const noexcept -> bool
	{
		return impl_ != nullptr;
	}

	auto get_id() const noexcept -> uint32_t
	{
		return SDL_GetWindowID(impl_.get());
	}

	auto get_brightness() const noexcept -> float
	{
		return SDL_GetWindowBrightness(impl_.get());
	}

	void set_brightness(float bright)
	{
		if(SDL_SetWindowBrightness(impl_.get(), bright))
		{
			OS_SDL_ERROR_HANDLER_VOID();
		}
	}

	void set_size(const area& size) noexcept
	{
		SDL_SetWindowSize(impl_.get(), static_cast<int>(size.w), static_cast<int>(size.h));
	}

	auto get_size() const noexcept -> area
	{
		area result{};
		int w{};
		int h{};
		SDL_GetWindowSize(impl_.get(), &w, &h);
		result.w = static_cast<uint32_t>(w);
		result.h = static_cast<uint32_t>(h);
		return result;
	}

	void set_maximum_size(const area& size) noexcept
	{
		SDL_SetWindowMaximumSize(impl_.get(), static_cast<int>(size.w), static_cast<int>(size.h));
	}

	auto get_maximum_size() const noexcept -> area
	{
		area result{};
		int w{};
		int h{};
		SDL_GetWindowMaximumSize(impl_.get(), &w, &h);
		result.w = static_cast<uint32_t>(w);
		result.h = static_cast<uint32_t>(h);

		return result;
	}

	void set_minimum_size(const area& size) noexcept
	{
		SDL_SetWindowMinimumSize(impl_.get(), static_cast<int>(size.w), static_cast<int>(size.h));
	}

	auto get_minimum_size() const noexcept -> area
	{
		area result;
		int w{};
		int h{};
		SDL_GetWindowMinimumSize(impl_.get(), &w, &h);
		result.w = static_cast<uint32_t>(w);
		result.h = static_cast<uint32_t>(h);
		return result;
	}

	void set_position(const point& pos) noexcept
	{
		SDL_SetWindowPosition(impl_.get(), static_cast<int>(pos.x), static_cast<int>(pos.y));
	}

	auto get_position() const noexcept -> point
	{
		point result;
		int x{};
		int y{};
		SDL_GetWindowPosition(impl_.get(), &x, &y);
		result.x = static_cast<int32_t>(x);
		result.y = static_cast<int32_t>(y);
		return result;
	}

	auto get_title() const noexcept -> std::string
	{
		return SDL_GetWindowTitle(impl_.get());
	}

	void set_title(const std::string& str) noexcept
	{
		SDL_SetWindowTitle(impl_.get(), str.c_str());
	}

	void show() noexcept
	{
		SDL_ShowWindow(impl_.get());
	}

	void hide() noexcept
	{
		SDL_HideWindow(impl_.get());
	}

	void maximize() noexcept
	{
		SDL_MaximizeWindow(impl_.get());
	}

	void minimize() noexcept
	{
		SDL_MinimizeWindow(impl_.get());
	}

	void restore() noexcept
	{
		SDL_RestoreWindow(impl_.get());
	}

	void raise() noexcept
	{
		SDL_RaiseWindow(impl_.get());
	}

	void set_border(bool b) noexcept
	{
		SDL_SetWindowBordered(impl_.get(), b ? SDL_TRUE : SDL_FALSE);
	}

	void set_fullscreen(bool b)
	{
		if(SDL_SetWindowFullscreen(impl_.get(), b ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0))
		{
			OS_SDL_ERROR_HANDLER_VOID();
		}
	}

	void set_opacity(float opacity)
	{
		if(SDL_SetWindowOpacity(impl_.get(), opacity))
		{
			OS_SDL_ERROR_HANDLER_VOID();
		}
	}

	auto get_opacity() const -> float
	{
		float opacity{1.0f};
		if(SDL_GetWindowOpacity(impl_.get(), &opacity))
		{
			OS_SDL_ERROR_HANDLER(opacity);
		}

		return opacity;
	}

	void grab_input(bool b) noexcept
	{
		SDL_SetWindowGrab(impl_.get(), b ? SDL_TRUE : SDL_FALSE);
	}

	bool is_input_grabbed() const noexcept
	{
		return SDL_GetWindowGrab(impl_.get()) != SDL_FALSE;
	}

	void request_focus()
	{
		if(SDL_SetWindowInputFocus(impl_.get()))
		{
			OS_SDL_ERROR_HANDLER_VOID();
		}
	}

	void set_cursor(const cursor& c) noexcept
	{
		SDL_SetCursor(to_cursor_impl(c).get_impl());
	}

	void show_cursor(bool show) noexcept
	{
		SDL_ShowCursor(show ? SDL_TRUE : SDL_FALSE);
	}

	void set_icon(const image& img)
	{
		auto surface =
			SDL_CreateRGBSurfaceFrom((void*)img.pixels.data(), int(img.size.w), int(img.size.h), 32,
									 int(img.size.w * 4), 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
		if(!surface)
		{
			OS_SDL_ERROR_HANDLER_VOID();
		}

		SDL_SetWindowIcon(impl_.get(), surface);
		SDL_FreeSurface(surface);
	}

private:
	std::unique_ptr<SDL_Window, window_deleter> impl_;
};
}
}
}
