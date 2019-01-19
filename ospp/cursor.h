#pragma once
#include <cstdint>
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
		arrow_wait,  /**< Small wait cursor (or Wait if not available) */
		wait,		 /**< Wait */
		ibeam,		 /**< I-beam */
		crosshair,   /**< Crosshair */
		size_nwse,   /**< Double arrow pointing northwest and southeast */
		size_nesw,   /**< Double arrow pointing northeast and southwest */
		size_we,	 /**< Double arrow pointing west and east */
		size_ns,	 /**< Double arrow pointing north and south */
		size_all,	/**< Four pointed arrow pointing north, south, east, and west */
		not_allowed, /**< Slashed circle or crossbones */
		hand,		 /**< Hand */
	};

	cursor(type system_type);

	auto get_impl() const noexcept -> void*;

private:
	std::shared_ptr<void> impl_;
};
} // sdl
