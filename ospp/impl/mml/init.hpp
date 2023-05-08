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
} // namespace mml
} // namespace detail
} // namespace os
