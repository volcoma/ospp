#pragma once
#include <cstdint>
namespace os
{
template <typename T>
struct vec2d
{
	T x{};
	T y{};
};

template <typename T>
struct area2d
{
	T w{};
	T h{};
};

using point = vec2d<int32_t>;
using area = area2d<uint32_t>;

} // os