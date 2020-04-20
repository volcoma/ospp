////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <mml/window/cursor.hpp>
#include <mml/window/cursor_impl.hpp>

namespace mml
{

////////////////////////////////////////////////////////////
cursor::cursor() :
impl_(new priv::cursor_impl())
{
    // That's it
}


////////////////////////////////////////////////////////////
cursor::~cursor()
{
    delete impl_;
}


////////////////////////////////////////////////////////////
bool cursor::load_from_pixels(const std::uint8_t* pixels, const std::array<std::uint32_t, 2>& size, const std::array<std::uint32_t, 2>& hotspot)
{
    if ((pixels == 0) || (size[0] == 0) || (size[1] == 0))
        return false;
    else
        return impl_->load_from_pixels(pixels, size, hotspot);
}


////////////////////////////////////////////////////////////
bool cursor::load_from_system(type t)
{
    return impl_->load_from_system(t);
}


////////////////////////////////////////////////////////////
const priv::cursor_impl& cursor::get_impl() const
{
    return *impl_;
}

} // namespace mml

