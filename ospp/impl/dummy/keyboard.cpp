#include "keyboard.h"


namespace os
{
    namespace key
    {
        os::key::code from_string(const std::string& str) noexcept
        {
            return {};
        }

        std::string to_string(os::key::code key_code) noexcept
        {
            return {};
        }

        bool is_pressed(os::key::code key_code) noexcept
        {
            return {};
        }
    }

    bool has_screen_keyboard() noexcept
    {
            return {};
    }

    void start_text_input() noexcept
    {
    }

    void stop_text_input() noexcept
    {
    }

    bool is_text_input_active() noexcept
    {
        return {};
    }
}
