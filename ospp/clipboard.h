#pragma once

#include <string>

namespace os
{
    namespace clipboard
    {
        auto get_text() noexcept -> std::string;
        void set_text(const std::string& text);
    }
}
