#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace os
{
    namespace display
    {
        struct mode
        {
            uint32_t w{};			 /**< width, in screen coordinates */
            uint32_t h{};			 /**< height, in screen coordinates */
            uint32_t refresh_rate{}; /**< refresh rate (or zero for unspecified) */
            uint32_t bpp{};			 /**< bits per pixel */
        };

        struct bounds
        {

            int x {};
            int y {};
            uint32_t w {};
            uint32_t h {};
        };

        auto enumerate_caps() -> void;
        auto get_available_displays_count() -> int;
        auto get_available_modes(int index = 0) -> std::vector<mode>;
        auto get_desktop_mode(int index = 0) -> mode;
        auto get_closest_mode(const mode& to, int index = 0) -> mode;
        auto get_closest_mode(uint32_t width, uint32_t height, int index = 0) -> mode;
        auto get_bounds(int index = 0) -> bounds;

        std::string to_string(const mode& m);
        std::string to_string(const bounds& b);
    }
}
