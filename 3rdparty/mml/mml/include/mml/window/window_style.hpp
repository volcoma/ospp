#ifndef MML_WINDOWSTYLE_HPP
#define MML_WINDOWSTYLE_HPP

#include <cstdint>

namespace mml
{
namespace style
{
    ////////////////////////////////////////////////////////////
    /// \ingroup window
    /// \brief Enumeration of the window styles
    ///
    ////////////////////////////////////////////////////////////
    enum : uint32_t
    {
        none            = 0,      ///< No border / title bar (this flag and all others are mutually exclusive)
        titlebar        = 1 << 0, ///< Title bar + fixed border
        resize          = 1 << 1, ///< Title bar + resizable border + maximize button
        close           = 1 << 2, ///< Title bar + close button
        fullscreen      = 1 << 3, ///< Fullscreen mode (this flag and all others are mutually exclusive)
        hidden          = 1 << 4,
        always_on_top   = 1 << 5,
        no_taskbar      = 1 << 6,

        utility         = 1 << 7,
        tooltip         = 1 << 8,
        popup_menu      = 1 << 9,

        standard        = titlebar | resize | close ///< standard window style
    };
}

} // namespace mml


#endif // MML_WINDOWSTYLE_HPP
