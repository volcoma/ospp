////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <mml/window/cursor_impl.hpp>
#include <mml/window/unix/display.hpp>
#include <X11/cursorfont.h>
#include <X11/Xutil.h>
#include <cassert>
#include <cstdlib>
#include <vector>

namespace mml
{
namespace priv
{

////////////////////////////////////////////////////////////
cursor_impl::cursor_impl() :
display_(open_display()),
cursor_(None)
{
    // That's it.
}


////////////////////////////////////////////////////////////
cursor_impl::~cursor_impl()
{
    release();

    close_display(display_);
}


////////////////////////////////////////////////////////////
bool cursor_impl::load_from_pixels(const std::uint8_t* pixels, std::array<std::uint32_t, 2> size, std::array<std::uint32_t, 2> hotspot)
{
    release();

    // Convert the image into a bitmap (monochrome!).
    std::size_t bytes = (size[0] + 7) / 8 * size[1];
    std::vector<std::uint8_t> mask(bytes, 0); // Defines which pixel is transparent.
    std::vector<std::uint8_t> data(bytes, 1); // Defines which pixel is white/black.

    for (std::size_t j = 0; j < size[1]; ++j)
    {
        for (std::size_t i = 0; i < size[0]; ++i)
        {
            std::size_t pixelIndex = i + j * size[0];
            std::size_t byteIndex  = pixelIndex / 8;
            std::size_t bitIndex   = i % 8;

            // Turn on pixel that are not transparent
            std::uint8_t opacity = pixels[pixelIndex * 4 + 3] > 0 ? 1 : 0;
            mask[byteIndex] |= opacity << bitIndex;

            // Choose between black/background & white/foreground color for each pixel,
            // based on the pixel color intensity: on average, if a channel is "active"
            // at 25%, the bit is white.
            int intensity = pixels[pixelIndex * 4 + 0] + pixels[pixelIndex * 4 + 1] + pixels[pixelIndex * 4 + 2];
            std::uint8_t bit = intensity > 64 ? 1 : 0;
            data[byteIndex] |= bit << bitIndex;
        }
    }

    Pixmap maskPixmap = XCreateBitmapFromData(display_, XDefaultRootWindow(display_),
                                              (char*)&mask[0], size[0], size[1]);
    Pixmap dataPixmap = XCreateBitmapFromData(display_, XDefaultRootWindow(display_),
                                              (char*)&data[0], size[0], size[1]);

    // Define the foreground color as white and the background as black.
    XColor fg, bg;
    fg.red = fg.blue = fg.green = -1;
    bg.red = bg.blue = bg.green =  0;

    // Create the monochrome cursor.
    cursor_ = XCreatePixmapCursor(display_,
                                   dataPixmap, maskPixmap,
                                   &fg, &bg,
                                   hotspot[0], hotspot[1]);

    // Free the resources
    XFreePixmap(display_, dataPixmap);
    XFreePixmap(display_, maskPixmap);

    // We assume everything went fine...
    return true;
}


////////////////////////////////////////////////////////////
bool cursor_impl::load_from_system(cursor::type type)
{
    release();

    unsigned int shape;
    switch (type)
    {
        default: return false;

        case cursor::arrow:           shape = XC_left_ptr;           break;
        case cursor::arrow_wait:      shape = XC_left_ptr;           break;
        case cursor::wait:            shape = XC_watch;              break;
        case cursor::text:            shape = XC_xterm;              break;
        case cursor::hand:            shape = XC_hand2;              break;
        case cursor::size_horizontal: shape = XC_sb_h_double_arrow;  break;
        case cursor::size_vertical:   shape = XC_sb_v_double_arrow;  break;
        case cursor::size_top_left_bottom_right: shape = XC_fleur; break;
        case cursor::size_bottom_left_top_right: shape = XC_fleur; break;
        case cursor::size_all:        shape = XC_fleur;              break;
        case cursor::cross:           shape = XC_tcross;             break;
        case cursor::help:            shape = XC_question_arrow;     break;
        case cursor::not_allowed:     shape = XC_X_cursor;           break;
    }

    cursor_ = XCreateFontCursor(display_, shape);
    return true;
}


////////////////////////////////////////////////////////////
void cursor_impl::release()
{
    if (cursor_ != None)
    {
        XFreeCursor(display_, cursor_);
        cursor_ = None;
    }
}


} // namespace priv

} // namespace mml

