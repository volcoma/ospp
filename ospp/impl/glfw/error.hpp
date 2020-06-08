#pragma once
#include "config.hpp"

#include <stdexcept>

namespace os
{
namespace detail
{
namespace glfw
{

inline auto last_error() -> std::string
{
	const char* result = nullptr;
    glfwGetError(&result);
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

#ifndef OS_GLFW_ERROR_HANDLER
#if defined(OS_NO_EXCEPTIONS)
#define OS_GLFW_ERROR_HANDLER_NO_RET()                                                                       \
	do                                                                                                       \
	{                                                                                                        \
        glfwGetError(nullptr);                                                                               \
	} while(0)
#define OS_GLFW_ERROR_HANDLER_VOID()                                                                         \
	do                                                                                                       \
	{                                                                                                        \
		OS_GLFW_ERROR_HANDLER_NO_RET();                                                                      \
		return;                                                                                              \
	} while(0)
#define OS_GLFW_ERROR_HANDLER(result)                                                                        \
	do                                                                                                       \
	{                                                                                                        \
		OS_GLFW_ERROR_HANDLER_NO_RET();                                                                      \
		return result;                                                                                       \
	} while(0)
#else
#define OS_GLFW_ERROR_HANDLER_NO_RET() throw ::os::detail::glfw::error()
#define OS_GLFW_ERROR_HANDLER_VOID() OS_GLFW_ERROR_HANDLER_NO_RET()
#define OS_GLFW_ERROR_HANDLER(result) OS_GLFW_ERROR_HANDLER_NO_RET()
#endif // OS_NO_EXCEPTIONS
#endif // OS_ERROR_HANDLER
} // sdl
}
}
