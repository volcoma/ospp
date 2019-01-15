#pragma once
#include <cstdlib>

namespace os
{
auto init() -> int;
void shutdown() noexcept;
}
