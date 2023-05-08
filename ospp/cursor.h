#pragma once

#include "types.hpp"

#include <cstdint>
#include <map>
#include <memory>

namespace os
{
class cursor
{
public:
	enum type : uint32_t
	{
		unknown,
		arrow,		 /**< Arrow */
		arrow_wait,	 /**< Small wait cursor (or Wait if not available) */
		wait,		 /**< Wait */
		ibeam,		 /**< I-beam */
		crosshair,	 /**< Crosshair */
		size_nwse,	 /**< Double arrow pointing northwest and southeast */
		size_nesw,	 /**< Double arrow pointing northeast and southwest */
		size_we,	 /**< Double arrow pointing west and east */
		size_ns,	 /**< Double arrow pointing north and south */
		size_all,	 /**< Four pointed arrow pointing north, south, east, and west */
		not_allowed, /**< Slashed circle or crossbones */
		hand,		 /**< Hand */
	};

	explicit cursor(type system_type);

	//-----------------------------------------------------------------------------
	/// \a image pixels must be an array of \a width by \a height pixels
	/// in 32-bit RGBA format. If not, this will cause undefined behavior.
	/// If image pixels are null or either the width or the height are 0,
	/// the input is considered invalid.
	///
	/// In addition to specifying the pixel data, you can also
	/// specify the location of the hotspot of the cursor. The
	/// hotspot is the pixel coordinate within the cursor image
	/// which will be located exactly where the mouse pointer
	/// position is. Any mouse actions that are performed will
	/// return the window/screen location of the hotspot.
	//-----------------------------------------------------------------------------
	cursor(const image& img, const point& hotspot = {});

	auto get_impl() const noexcept -> void*;

private:
	std::shared_ptr<void> impl_;
};

std::map<cursor::type, cursor>& system_cursors();
const cursor& get_system_cursor(cursor::type type);
} // namespace os
