#include "mouse.h"

namespace os
{
    namespace mouse
    {
        auto is_button_pressed(button b) noexcept -> bool
        {
            return {};
        }

        auto get_position() noexcept -> point
        {
            return {};
        }

        auto get_position(const window& relative_to) noexcept -> point
        {
            return {};
        }

        void set_position(const point& pos) noexcept
        {
        }

        void set_position(const point& pos, const window& relative_to) noexcept
        {
        }
    }
}
