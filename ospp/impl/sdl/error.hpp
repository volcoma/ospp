#pragma once
#include "config.hpp"

#include <stdexcept>

namespace os
{
namespace detail
{
namespace sdl
{

inline auto last_error() -> std::string
{
	const char* result = SDL_GetError();
	SDL_ClearError();
	return result;
}
class error : public std::runtime_error
{
public:
	error()
		: std::runtime_error(last_error())
	{
	}

	error(const std::string& str)
		: std::runtime_error(str)
	{
	}
};

#ifndef OS_SDL_ERROR_HANDLER
#if defined(OS_NO_EXCEPTIONS)
#define OS_SDL_ERROR_HANDLER_NO_RET()                                                                        \
	do                                                                                                       \
	{                                                                                                        \
		::SDL_Log("%s", last_error().c_str());                                                               \
	} while(0)
#define OS_SDL_ERROR_HANDLER_VOID()                                                                          \
	do                                                                                                       \
	{                                                                                                        \
		OS_SDL_ERROR_HANDLER_NO_RET();                                                                       \
		return;                                                                                              \
	} while(0)
#define OS_SDL_ERROR_HANDLER(result)                                                                         \
	do                                                                                                       \
	{                                                                                                        \
		OS_SDL_ERROR_HANDLER_NO_RET();                                                                       \
		return result;                                                                                       \
	} while(0)
#else
#define OS_SDL_ERROR_HANDLER_NO_RET() throw ::os::detail::sdl::error()
#define OS_SDL_ERROR_HANDLER_VOID() OS_SDL_ERROR_HANDLER_NO_RET()
#define OS_SDL_ERROR_HANDLER(result) OS_SDL_ERROR_HANDLER_NO_RET()
#endif // OS_NO_EXCEPTIONS
#endif // OS_ERROR_HANDLER
} // sdl
}
}
