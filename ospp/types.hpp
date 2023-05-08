#pragma once
#include <cstdint>
#include <vector>

namespace os
{
template <typename T>
struct vec2d
{
	vec2d() = default;
	vec2d(T xval, T yval)
		: x(xval)
		, y(yval)
	{
	}

	T x{};
	T y{};
};

template <typename T>
struct area2d
{
	area2d() = default;
	area2d(T wval, T hval)
		: w(wval)
		, h(hval)
	{
	}

	T w{};
	T h{};
};

using point = vec2d<int32_t>;
using area = area2d<uint32_t>;

struct image
{
	std::vector<uint8_t> pixels;
	area size{};
};
} // namespace os
