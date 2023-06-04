#pragma once
#include "error.hpp"

namespace os
{
namespace detail
{
namespace mml
{
inline void shutdown() noexcept
{
}

inline auto init() -> bool
{
	return true;
}

inline auto get_current_backend() -> const char*
{
    return "MML";
}
} // namespace mml
} // namespace detail
} // namespace os
