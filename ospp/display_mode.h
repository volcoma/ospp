#pragma once
#include <cstdint>
#include <vector>

namespace os
{
auto number_of_video_displays() -> int;

struct display_mode
{
	static auto get_available_modes(int index = 0) -> std::vector<display_mode>;
	static auto get_desktop_mode(int index = 0) -> display_mode;
	static auto get_closest_mode(const display_mode& to, int index = 0) -> display_mode;
	static auto get_closest_mode(uint32_t width, uint32_t height, int index = 0) -> display_mode;

	uint32_t w{};			 /**< width, in screen coordinates */
	uint32_t h{};			 /**< height, in screen coordinates */
	uint32_t refresh_rate{}; /**< refresh rate (or zero for unspecified) */
    uint32_t bpp{}; /**< bits per pixel */
};
}
