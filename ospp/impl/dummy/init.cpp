#include "init.h"
#include "cursor.h"

namespace os
{
    void shutdown() noexcept
    {
        system_cursors().clear();
    }

    auto init() -> bool
    {
        return true;
    }
}
