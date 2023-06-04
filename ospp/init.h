#pragma once

namespace os
{
auto init() -> bool;
void shutdown() noexcept;

auto get_current_backend() -> const char*;
} // namespace os
